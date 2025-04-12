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
 * \brief Definition of functions of dash sequences.
 */
#pragma once

#include <string>
#include <vector>

namespace plotly_plotter::figure_builders {

/*!
 * \brief Get the default dash sequence.
 *
 * \return Dash sequence.
 */
[[nodiscard]] inline std::vector<std::string> dash_sequence_default() {
    return {
        "solid",
        "dot",
        "dash",
        "longdash",
        "dashdot",
        "longdashdot",
    };
}

}  // namespace plotly_plotter::figure_builders
