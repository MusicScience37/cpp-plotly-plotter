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
 * \brief Implementation of html_to_pdf function.
 */
#include "plotly_plotter/details/html_to_pdf.h"

#include <stdexcept>

#ifdef linux
#include <array>
#include <cerrno>
#include <chrono>
#include <cstdio>
#include <string>
#include <thread>
#include <vector>

#include <fcntl.h>
#include <fmt/format.h>
#include <stdlib.h>  // NOLINT
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace plotly_plotter::details {

#ifdef linux

void html_to_pdf(const char* html_file_path, const char* pdf_file_path,
    std::size_t width, std::size_t height, bool capture_logs) {
    std::vector<std::string> command{"google-chrome", "--headless",
        fmt::format("--print-to-pdf={}", pdf_file_path),
        fmt::format("--window-size={},{}", width, height),
        "--no-pdf-header-footer",
        // --no-sandbox is required for running chrome as root user.
        "--no-sandbox", html_file_path};

    std::vector<char*> argv;
    argv.reserve(command.size() + 1);
    for (auto& arg : command) {
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
            perror("Failed to execute chrome for PDF generation");
            exit(1);  // NOLINT(concurrency-mt-unsafe)
        }

        // This line should not be reached
        exit(2);  // NOLINT(concurrency-mt-unsafe)
    }

    std::string command_output;
    if (capture_logs) {
        command_output =
            "\n"
            "Output from chrome:\n";

        close(pipe_descriptors[1]);

        if (fcntl(pipe_descriptors[0], F_SETFL, O_NONBLOCK) == -1) {
            perror("Failed to set the pipe to non-blocking mode");
            close(pipe_descriptors[0]);
            return;
        }

        constexpr std::size_t buffer_size = 1024;
        char buffer[buffer_size];
        const auto deadline =
            std::chrono::steady_clock::now() + std::chrono::seconds(30);
        while (true) {
            ssize_t read_result =
                read(pipe_descriptors[0], buffer, sizeof(buffer));
            if (read_result == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    if (std::chrono::steady_clock::now() > deadline) {
                        throw std::runtime_error(fmt::format(
                            "Chrome took too long to generate PDF.{}",
                            command_output));
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
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

    // Parent process
    int status{};
    pid_t wait_result = waitpid(pid, &status, 0);
    if (wait_result == -1) {
        const auto error_number = errno;
        throw std::runtime_error(
            fmt::format("Failed to wait for the child process with error {}.{}",
                error_number, command_output));
    }

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        if (WIFSIGNALED(status)) {
            throw std::runtime_error(
                fmt::format("Failed to generate PDF with signal {}.{}",
                    WTERMSIG(status), command_output));
        }
        throw std::runtime_error(
            fmt::format("Failed to generate PDF with status {}.{}",
                WEXITSTATUS(status), command_output));
    }
}

#else

void html_to_pdf(const char* html_file_path, const char* pdf_file_path,
    std::size_t width, std::size_t height) {
    (void)html_file_path;
    (void)pdf_file_path;
    (void)width;
    (void)height;
    throw std::runtime_error("PDF is not supported for this platform.");
}

#endif

}  // namespace plotly_plotter::details
