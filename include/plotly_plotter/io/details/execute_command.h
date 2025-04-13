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
 * \brief Declaration of functions to execute commands.
 */
#pragma once

#include <string>
#include <vector>

#include "plotly_plotter/details/plotly_plotter_export.h"

namespace plotly_plotter::io::details {

/*!
 * \brief Check if a command executes successfully.
 *
 * \param[in] command Command.
 * \param[in] capture_logs Whether to capture logs.
 * \retval true Command executed successfully.
 * \retval false Command failed.
 *
 * \note This function throws exceptions only when a system call fails.
 * \note This function returns false when command execution in the environment
 * is not supported by this library.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT bool check_command_success(
    const std::vector<std::string>& command, bool capture_logs = true);

/*!
 * \brief Execute a command.
 *
 * \param[in] command Command.
 * \param[in] capture_logs Whether to capture logs.
 *
 * \note This function throws exceptions when the command fails or a system call
 * fails.
 */
PLOTLY_PLOTTER_EXPORT void execute_command(
    const std::vector<std::string>& command, bool capture_logs = true);

}  // namespace plotly_plotter::io::details
