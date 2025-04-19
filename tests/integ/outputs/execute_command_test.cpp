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

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/details/config.h"

TEST_CASE("plotly_plotter::io::details::execute_command") {
    SECTION("check command execution") {
#if PLOTLY_PLOTTER_USE_UNIX_SUBPROCESS
        SECTION("success") {
            std::vector<std::string> command{"ls", "-l"};
            const bool capture_logs = true;
            CHECK(plotly_plotter::io::details::check_command_success(
                command, capture_logs));
        }

        SECTION("failure in command") {
            std::vector<std::string> command{"ls", "non_existent_file"};
            const bool capture_logs = true;
            CHECK_FALSE(plotly_plotter::io::details::check_command_success(
                command, capture_logs));
        }

        SECTION("failure in starting the command") {
            std::vector<std::string> command{"non_existent_command"};
            const bool capture_logs = true;
            CHECK_FALSE(plotly_plotter::io::details::check_command_success(
                command, capture_logs));
        }
#elif PLOTLY_PLOTTER_USE_WIN_SUBPROCESS
        SECTION("success") {
            std::vector<std::string> command{"python", "--version"};
            const bool capture_logs = true;
            CHECK(plotly_plotter::io::details::check_command_success(
                command, capture_logs));
        }

        SECTION("failure in command") {
            std::vector<std::string> command{"python", "non_existent_file"};
            const bool capture_logs = true;
            CHECK_FALSE(plotly_plotter::io::details::check_command_success(
                command, capture_logs));
        }

        SECTION("failure in starting the command") {
            std::vector<std::string> command{"non_existent_command"};
            const bool capture_logs = true;
            CHECK_FALSE(plotly_plotter::io::details::check_command_success(
                command, capture_logs));
        }
#else
        std::vector<std::string> command{"ls", "-l"};
        const bool capture_logs = true;
        CHECK_FALSE(plotly_plotter::io::details::check_command_success(
            command, capture_logs));
#endif
    }

    SECTION("execute a command") {
#if PLOTLY_PLOTTER_USE_UNIX_SUBPROCESS
        SECTION("success") {
            std::vector<std::string> command{"ls", "-l"};
            const bool capture_logs = true;
            CHECK_NOTHROW(plotly_plotter::io::details::execute_command(
                command, capture_logs));
        }

        SECTION("failure in command") {
            std::vector<std::string> command{"ls", "non_existent_file"};
            const bool capture_logs = true;
            CHECK_THROWS(plotly_plotter::io::details::execute_command(
                command, capture_logs));
        }

        SECTION("failure in starting the command") {
            std::vector<std::string> command{"non_existent_command"};
            const bool capture_logs = true;
            CHECK_THROWS(plotly_plotter::io::details::execute_command(
                command, capture_logs));
        }
#elif PLOTLY_PLOTTER_USE_WIN_SUBPROCESS
        SECTION("success") {
            std::vector<std::string> command{"python", "--version"};
            const bool capture_logs = true;
            CHECK_NOTHROW(plotly_plotter::io::details::execute_command(
                command, capture_logs));
        }

        SECTION("failure in command") {
            std::vector<std::string> command{"python", "non_existent_file"};
            const bool capture_logs = true;
            CHECK_THROWS(plotly_plotter::io::details::execute_command(
                command, capture_logs));
        }

        SECTION("failure in starting the command") {
            std::vector<std::string> command{"non_existent_command"};
            const bool capture_logs = true;
            CHECK_THROWS(plotly_plotter::io::details::execute_command(
                command, capture_logs));
        }
#else
        std::vector<std::string> command{"ls", "-l"};
        const bool capture_logs = true;
        CHECK_THROWS(plotly_plotter::io::details::execute_command(
            command, capture_logs));
#endif
    }
}
