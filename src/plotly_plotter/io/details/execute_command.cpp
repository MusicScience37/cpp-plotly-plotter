/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*!
 * \file
 * \brief Implementation of functions to execute commands.
 */
#include "plotly_plotter/io/details/execute_command.h"

#include <stdexcept>

#include "plotly_plotter/details/config.h"

#if PLOTLY_PLOTTER_USE_UNIX_SUBPROCESS

#include <array>
#include <cerrno>
#include <chrono>
#include <cstdio>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <fcntl.h>
#include <fmt/format.h>
#include <signal.h>  // NOLINT: for some Linux APIs.
#include <stdlib.h>  // NOLINT: for some Linux APIs.
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace plotly_plotter::io::details {

/*!
 * \brief Execute a command.
 *
 * \param[in] command Command.
 * \param[in] capture_logs Whether to capture logs.
 * \return Exit status and output of the command.
 */
[[nodiscard]] inline std::pair<int, std::string> execute_command_impl(
    const std::vector<std::string>& command, bool capture_logs) {
    std::vector<std::string> command_copy = command;
    std::vector<char*> argv;
    argv.reserve(command.size() + 1);
    for (auto& arg : command_copy) {
        argv.push_back(arg.data());
    }
    argv.push_back(nullptr);

    std::array<int, 2> pipe_descriptors{};
    if (capture_logs) {
        if (pipe(pipe_descriptors.data()) == -1) {
            throw std::runtime_error("Failed to create a pipe.");
        }
    }

    pid_t pid = fork();
    if (pid == -1) {
        throw std::runtime_error("Failed to fork.");
    }

    if (pid == 0) {
        // Child process
        if (capture_logs) {
            close(pipe_descriptors[0]);
            if (dup2(pipe_descriptors[1], STDOUT_FILENO) == -1) {
                perror("Failed to redirect stdout");
                exit(1);  // NOLINT(concurrency-mt-unsafe)
            }
            if (dup2(pipe_descriptors[1], STDERR_FILENO) == -1) {
                perror("Failed to redirect stderr");
                exit(1);  // NOLINT(concurrency-mt-unsafe)
            }
            close(pipe_descriptors[1]);
        }

        int result = execvp(argv[0], argv.data());
        if (result == -1) {
            perror("Failed to execute child process");
            exit(1);  // NOLINT(concurrency-mt-unsafe)
        }

        // This line should not be reached
        exit(2);  // NOLINT(concurrency-mt-unsafe)
    }

    std::string command_output;
    if (capture_logs) {
        command_output =
            "\n"
            "Output from a process:\n";

        close(pipe_descriptors[1]);

        if (fcntl(pipe_descriptors[0], F_SETFL, O_NONBLOCK) == -1) {
            perror("Failed to set the pipe to non-blocking mode");
        }

        constexpr std::size_t buffer_size = 1024;
        char buffer[buffer_size];
        const auto deadline =
            std::chrono::steady_clock::now() + std::chrono::seconds(10);
        while (true) {
            ssize_t read_result =
                read(pipe_descriptors[0], buffer, sizeof(buffer));
            if (read_result == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    if (std::chrono::steady_clock::now() > deadline) {
                        kill(pid, SIGTERM);
                        throw std::runtime_error(fmt::format(
                            "Timeout in child process.{}", command_output));
                    }
                    // NOLINTNEXTLINE
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    continue;
                }
                perror("Failed to read from the pipe");
                break;
            }
            if (read_result == 0) {
                break;
            }
            command_output.append(
                buffer, static_cast<std::size_t>(read_result));
        }
        close(pipe_descriptors[0]);
    }

    int status{};
    pid_t wait_result = waitpid(pid, &status, 0);
    if (wait_result == -1) {
        const auto error_number = errno;
        throw std::runtime_error(
            fmt::format("Failed to wait for the child process with error {}.{}",
                error_number, command_output));
    }

    return {status, command_output};
}

bool check_command_success(
    const std::vector<std::string>& command, bool capture_logs) {
    if (command.empty()) {
        throw std::invalid_argument("Command is empty.");
    }

    const auto [status, command_output] =
        execute_command_impl(command, capture_logs);

    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

void execute_command(
    const std::vector<std::string>& command, bool capture_logs) {
    if (command.empty()) {
        throw std::invalid_argument("Command is empty.");
    }

    const auto [status, command_output] =
        execute_command_impl(command, capture_logs);

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        if (WIFSIGNALED(status)) {
            throw std::runtime_error(
                fmt::format("Failed to execute {} with signal {}.{}",
                    command.front(), WTERMSIG(status), command_output));
        }
        throw std::runtime_error(
            fmt::format("Failed to execute {} with status {}.{}",
                command.front(), WEXITSTATUS(status), command_output));
    }
}

}  // namespace plotly_plotter::io::details

#elif PLOTLY_PLOTTER_USE_WIN_SUBPROCESS

// clang-format off
// This must be included before any other Windows headers
// to avoid compile errors.
#include <windows.h>
#include <namedpipeapi.h>
#include <processthreadsapi.h>
// clang-format on

#include <thread>
#include <tuple>

#include <fmt/format.h>

namespace plotly_plotter::io::details {

/*!
 * \brief Close a handle if it is not null.
 *
 * @param[in] handle Handle to close.
 */
void close_handle_if_not_null(HANDLE handle) noexcept {
    if (handle != nullptr) {
        CloseHandle(handle);
    }
}

/*!
 * \brief Execute a command.
 *
 * \param[in] command Command.
 * \param[in] capture_logs Whether to capture logs.
 * \return Whether command execution started successfully,
 * exit code and output of the command.
 */
[[nodiscard]] inline std::tuple<bool, DWORD, std::string> execute_command_impl(
    const std::vector<std::string>& command, bool capture_logs) {
    std::string command_line;
    for (const auto& arg : command) {
        command_line += "\"" + arg + "\" ";
    }

    HANDLE stdin_pipe_read = nullptr;
    HANDLE stdin_pipe_write = nullptr;
    HANDLE stdout_pipe_read = nullptr;
    HANDLE stdout_pipe_write = nullptr;
    SECURITY_ATTRIBUTES security_attributes_for_pipe;
    security_attributes_for_pipe.nLength = sizeof(SECURITY_ATTRIBUTES);
    security_attributes_for_pipe.bInheritHandle = TRUE;
    security_attributes_for_pipe.lpSecurityDescriptor = nullptr;
    if (capture_logs) {
        if (!CreatePipe(&stdin_pipe_read, &stdin_pipe_write,
                &security_attributes_for_pipe, 0)) {
            throw std::runtime_error("Failed to create a pipe for subprocess.");
        }
        if (!SetHandleInformation(stdin_pipe_write, HANDLE_FLAG_INHERIT, 0)) {
            close_handle_if_not_null(stdin_pipe_read);
            close_handle_if_not_null(stdin_pipe_write);
            throw std::runtime_error(
                "Failed to set handle information for subprocess.");
        }
        if (!CreatePipe(&stdout_pipe_read, &stdout_pipe_write,
                &security_attributes_for_pipe, 0)) {
            close_handle_if_not_null(stdin_pipe_read);
            close_handle_if_not_null(stdin_pipe_write);
            throw std::runtime_error("Failed to create a pipe for subprocess.");
        }
        if (!SetHandleInformation(stdout_pipe_read, HANDLE_FLAG_INHERIT, 0)) {
            close_handle_if_not_null(stdin_pipe_read);
            close_handle_if_not_null(stdin_pipe_write);
            close_handle_if_not_null(stdout_pipe_read);
            close_handle_if_not_null(stdout_pipe_write);
            throw std::runtime_error(
                "Failed to set handle information for subprocess.");
        }
    }

    STARTUPINFO startup_info;
    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    if (capture_logs) {
        startup_info.hStdInput = stdin_pipe_read;
        startup_info.hStdOutput = stdout_pipe_write;
        startup_info.hStdError = stdout_pipe_write;
        startup_info.dwFlags |= STARTF_USESTDHANDLES;
    }

    PROCESS_INFORMATION process_info;
    ZeroMemory(&process_info, sizeof(process_info));

    if (!CreateProcess(nullptr, command_line.data(), nullptr, nullptr, TRUE, 0,
            nullptr, nullptr, &startup_info, &process_info)) {
        close_handle_if_not_null(stdin_pipe_read);
        close_handle_if_not_null(stdin_pipe_write);
        close_handle_if_not_null(stdout_pipe_read);
        close_handle_if_not_null(stdout_pipe_write);
        const DWORD error_code = GetLastError();
        return {false, error_code, ""};
    }

    // Close unused handles.
    close_handle_if_not_null(stdin_pipe_read);
    close_handle_if_not_null(stdin_pipe_write);
    close_handle_if_not_null(stdout_pipe_write);

    std::string command_output;
    std::thread command_output_reader_thread;
    if (capture_logs) {
        command_output_reader_thread =
            std::thread([stdout_pipe_read, &command_output] {
                command_output =
                    "\n"
                    "Output from a process:\n";

                constexpr std::size_t buffer_size = 1024;
                char buffer[buffer_size]{};
                DWORD bytes_read;
                while (true) {
                    bytes_read = 0;
                    const BOOL read_result = ReadFile(stdout_pipe_read, buffer,
                        sizeof(buffer), &bytes_read, nullptr);
                    if (bytes_read == 0) {
                        break;
                    }
                    command_output.append(
                        buffer, static_cast<std::size_t>(bytes_read));
                    if (!read_result) {
                        break;
                    }
                }
            });
    }

    constexpr DWORD wait_timeout_msec = 10000;  // 10 seconds
    const DWORD wait_result =
        WaitForSingleObject(process_info.hProcess, wait_timeout_msec);
    if (wait_result == WAIT_TIMEOUT) {
        TerminateProcess(process_info.hProcess, 1);
        if (command_output_reader_thread.joinable()) {
            command_output_reader_thread.join();
        }
        close_handle_if_not_null(process_info.hProcess);
        close_handle_if_not_null(process_info.hThread);
        throw std::runtime_error(
            fmt::format("Timeout in child process.{}", command_output));
    }
    if (wait_result != WAIT_OBJECT_0) {
        TerminateProcess(process_info.hProcess, 1);
        if (command_output_reader_thread.joinable()) {
            command_output_reader_thread.join();
        }
        close_handle_if_not_null(process_info.hProcess);
        close_handle_if_not_null(process_info.hThread);
        throw std::runtime_error(fmt::format(
            "Failed to wait for the child process.{}", command_output));
    }

    if (command_output_reader_thread.joinable()) {
        command_output_reader_thread.join();
    }

    DWORD exit_code;
    if (!GetExitCodeProcess(process_info.hProcess, &exit_code)) {
        close_handle_if_not_null(process_info.hProcess);
        close_handle_if_not_null(process_info.hThread);
        throw std::runtime_error(
            fmt::format("Failed to get exit code.{}", command_output));
    }

    close_handle_if_not_null(process_info.hProcess);
    close_handle_if_not_null(process_info.hThread);

    return {true, exit_code, command_output};
}

bool check_command_success(
    const std::vector<std::string>& command, bool capture_logs) {
    if (command.empty()) {
        throw std::invalid_argument("Command is empty.");
    }
    const auto [started, exit_code, command_output] =
        execute_command_impl(command, capture_logs);
    return started && exit_code == 0;
}

void execute_command(
    const std::vector<std::string>& command, bool capture_logs) {
    if (command.empty()) {
        throw std::invalid_argument("Command is empty.");
    }

    const auto [started, exit_code, command_output] =
        execute_command_impl(command, capture_logs);

    if (!started) {
        throw std::runtime_error(
            fmt::format("Failed to start the command {} with an error {}.",
                command[0], exit_code));
    }

    if (exit_code != 0) {
        throw std::runtime_error(
            fmt::format("Failed to execute {} with exit code {}.{}", command[0],
                exit_code, command_output));
    }
}

}  // namespace plotly_plotter::io::details

#else

namespace plotly_plotter::io::details {

bool check_command_success(
    const std::vector<std::string>& command, bool capture_logs) {
    (void)command;
    (void)capture_logs;
    return false;
}

void execute_command(
    const std::vector<std::string>& command, bool capture_logs) {
    (void)command;
    (void)capture_logs;
    throw std::runtime_error(
        "Command execution is not supported for this platform.");
}

}  // namespace plotly_plotter::io::details

#endif
