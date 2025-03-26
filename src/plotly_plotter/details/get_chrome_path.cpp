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
 * \brief Definition of get_chrome_path function.
 */
#include "plotly_plotter/details/get_chrome_path.h"

#include <string>
#include <string_view>
#include <vector>

#include "plotly_plotter/details/execute_command.h"

#ifdef linux
#include <stdlib.h>  // NOLINT
#endif

namespace plotly_plotter::details {

namespace {

#ifdef linux

[[nodiscard]] bool check_executable_exists(const std::string& executable_path) {
    std::vector<std::string> command{executable_path, "--version"};

    const auto [status, command_output] = execute_command(command, true);

    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

[[nodiscard]] std::string find_chrome_path() {
    const std::vector<std::string> possible_paths{
        "google-chrome", "google-chrome-stable", "chrome"};
    for (const auto& path : possible_paths) {
        if (check_executable_exists(path)) {
            return path;
        }
    }
    return possible_paths.front();
}

#else

[[nodiscard]] std::string find_chrome_path() { return "chrome"; }

#endif

}  // namespace

std::string_view get_chrome_path() {
    static const std::string chrome_path = find_chrome_path();
    return chrome_path;
}

}  // namespace plotly_plotter::details
