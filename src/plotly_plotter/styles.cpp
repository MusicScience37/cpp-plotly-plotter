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
 * \brief Implementation of functions of styles of figures.
 */
#include "plotly_plotter/styles.h"

#include <string_view>

namespace plotly_plotter::styles {

void simple_style(plotly_plotter::layout layout, std::size_t num_xaxes,
    std::size_t num_yaxes) {
    layout.title().x(0.05);  // NOLINT
    for (std::size_t i = 0; i < num_xaxes; ++i) {
        layout.xaxis(i + 1).show_line(true);
        layout.xaxis(i + 1).line_color("#242424");
        layout.xaxis(i + 1).grid_color("#C8C8C8");
        layout.xaxis(i + 1).zero_line_color("#C8C8C8");
        layout.xaxis(i + 1).ticks("outside");
    }
    for (std::size_t i = 0; i < num_yaxes; ++i) {
        layout.yaxis(i + 1).show_line(true);
        layout.yaxis(i + 1).line_color("#242424");
        layout.yaxis(i + 1).grid_color("#C8C8C8");
        layout.yaxis(i + 1).zero_line_color("#C8C8C8");
        layout.yaxis(i + 1).ticks("outside");
    }
}

}  // namespace plotly_plotter::styles
