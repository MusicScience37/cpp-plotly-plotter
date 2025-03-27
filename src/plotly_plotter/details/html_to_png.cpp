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
 * \brief Implementation of html_to_png function.
 */
#include "plotly_plotter/details/html_to_png.h"

#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <fmt/format.h>

#include "plotly_plotter/details/execute_command.h"
#include "plotly_plotter/details/get_chrome_path.h"

#ifdef linux
#include <stdlib.h>  // NOLINT
#endif

namespace plotly_plotter::details {

#ifdef linux
bool is_png_supported() {
    std::vector<std::string> command{
        static_cast<std::string>(get_chrome_path()), "--version"};

    const auto [status, command_output] = execute_command(command, true);

    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

void html_to_png(const char* html_file_path, const char* png_file_path,
    std::size_t width, std::size_t height, bool capture_logs) {
    std::vector<std::string> command{
        static_cast<std::string>(get_chrome_path()), "--headless",
        fmt::format("--screenshot={}", png_file_path),
        fmt::format("--window-size={},{}", width, height),
        // --no-sandbox is required for running chrome as root user.
        "--no-sandbox",
        // GPU can not be used in ordinary Docker containers.
        "--disable-gpu", html_file_path};

    const auto [status, command_output] =
        execute_command(command, capture_logs);

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        if (WIFSIGNALED(status)) {
            throw std::runtime_error(
                fmt::format("Failed to generate PNG with signal {}.{}",
                    WTERMSIG(status), command_output));
        }
        throw std::runtime_error(
            fmt::format("Failed to generate PNG with status {}.{}",
                WEXITSTATUS(status), command_output));
    }
}

#else

bool is_png_supported() { return false; }

void html_to_png(const char* html_file_path, const char* png_file_path,
    std::size_t width, std::size_t height, bool capture_logs) {
    (void)html_file_path;
    (void)png_file_path;
    (void)width;
    (void)height;
    (void)capture_logs;
    throw std::runtime_error("PNG is not supported for this platform.");
}

#endif

}  // namespace plotly_plotter::details
