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
 * \brief Definition of functions of color sequences.
 */
#pragma once

#include <string>
#include <vector>

namespace plotly_plotter::figure_builders {

/*!
 * \brief Get the color sequence used in Plotly.
 *
 * \return Color sequence.
 */
[[nodiscard]] inline std::vector<std::string> color_sequence_plotly() {
    return {"rgb(31, 119, 180)", "rgb(255, 127, 14)", "rgb(44, 160, 44)",
        "rgb(214, 39, 40)", "rgb(148, 103, 189)", "rgb(140, 86, 75)",
        "rgb(227, 119, 194)", "rgb(127, 127, 127)", "rgb(188, 189, 34)",
        "rgb(23, 190, 207)"};
}

}  // namespace plotly_plotter::figure_builders
