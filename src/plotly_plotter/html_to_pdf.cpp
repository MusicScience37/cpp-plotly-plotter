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

#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

#include <fmt/format.h>

#ifdef linux
#include <stdlib.h>  // NOLINT
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace plotly_plotter::details {

#ifdef linux

void html_to_pdf(const char* html_file_path, const char* pdf_file_path,
    std::size_t width, std::size_t height) {
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

    pid_t pid = fork();
    if (pid == -1) {
        throw std::runtime_error("Failed to fork.");
    }

    if (pid == 0) {
        // Child process
        int result = execvp(argv[0], argv.data());
        if (result == -1) {
            perror("Failed to execute chrome for PDF generation");
            exit(1);  // NOLINT(concurrency-mt-unsafe)
        }

        // This line should not be reached
        exit(2);  // NOLINT(concurrency-mt-unsafe)
    }

    // Parent process
    int status{};
    pid_t wait_result = waitpid(pid, &status, 0);
    if (wait_result == -1) {
        const auto error_number = errno;
        throw std::runtime_error(
            fmt::format("Failed to wait for the child process with error {}.",
                error_number));
    }

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        if (WIFSIGNALED(status)) {
            throw std::runtime_error(fmt::format(
                "Failed to generate PDF with signal {}.", WTERMSIG(status)));
        }
        throw std::runtime_error(fmt::format(
            "Failed to generate PDF with status {}.", WEXITSTATUS(status)));
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
