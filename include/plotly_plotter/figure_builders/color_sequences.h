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
 * \brief Definition of functions color sequences.
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
    return {"#636EFA", "#EF553B", "#00CC96", "#AB63FA", "#FFA15A", "#19D3F3",
        "#FF6692", "#B6E880", "#FF97FF", "#FECB52"};
}

}  // namespace plotly_plotter::figure_builders
