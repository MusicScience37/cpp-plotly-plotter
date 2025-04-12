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
 * \brief Example to set axes to log scale.
 */
#include <plotly_plotter/data_table.h>
#include <plotly_plotter/figure.h>
#include <plotly_plotter/figure_builders/scatter.h>
#include <plotly_plotter/write_html.h>

int main() {
    // Prepare data.
    plotly_plotter::data_table data;
    data.emplace("x", std::vector{1, 10, 100});
    data.emplace("y", std::vector{1, 123, 4567});

    // Create a figure.
    const plotly_plotter::figure figure =
        plotly_plotter::figure_builders::scatter(data)
            .x("x")
            .y("y")
            // Set log scale.
            .log_x(true)
            .log_y(true)
            .title("Scatter Plot with Log Scale Axes")
            .create();

    // Save the figure to a HTML file.
    plotly_plotter::write_html(
        "figure_builders_set_axes_to_log_scale.html", figure);
}
