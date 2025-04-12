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
 * \brief Definition of internal common functions of figure builders.
 */
#include "plotly_plotter/figure_builders/details/figure_builder_helper.h"

#include "plotly_plotter/layout.h"

namespace plotly_plotter::figure_builders::details {

void configure_axes_common(figure& fig, std::size_t num_subplot_rows,
    std::size_t num_subplot_columns, std::string_view x_title,
    std::string_view y_title) {
    // Titles of axes.
    if (!x_title.empty()) {
        for (std::size_t i = 0; i < num_subplot_columns; ++i) {
            const std::size_t index =
                (num_subplot_rows - 1) * num_subplot_columns + i + 1;
            fig.layout().xaxis(index).title().text(x_title);
        }
    }
    for (std::size_t i = 0; i < num_subplot_rows; ++i) {
        const std::size_t index = i * num_subplot_columns + 1;
        fig.layout().yaxis(index).title().text(y_title);
    }

    // Hide duplicate tick labels.
    for (std::size_t row = 0; row < num_subplot_rows - 1; ++row) {
        for (std::size_t column = 0; column < num_subplot_columns; ++column) {
            const std::size_t index = row * num_subplot_columns + column + 1;
            fig.layout().xaxis(index).show_tick_labels(false);
        }
    }
    for (std::size_t column = 1; column < num_subplot_columns; ++column) {
        for (std::size_t row = 0; row < num_subplot_rows; ++row) {
            const std::size_t index = row * num_subplot_columns + column + 1;
            fig.layout().yaxis(index).show_tick_labels(false);
        }
    }

    // Configure to use same ranges.
    for (std::size_t i = 1; i < num_subplot_rows * num_subplot_columns; ++i) {
        const std::size_t index = i + 1;
        fig.layout().xaxis(index).matches("x");
        fig.layout().yaxis(index).matches("y");
    }
}

}  // namespace plotly_plotter::figure_builders::details
