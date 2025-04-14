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
 * \brief Example to colorize markers in a figure builder.
 */
#include <plotly_plotter/data_table.h>
#include <plotly_plotter/figure.h>
#include <plotly_plotter/figure_builders/scatter.h>
#include <plotly_plotter/write_html.h>

int main() {
    // Prepare data.
    plotly_plotter::data_table data;
    data.emplace("x", std::vector{1, 2, 3});
    data.emplace("y", std::vector{1.2, 2.3, 3.4});
    data.emplace("Color", std::vector{2.0, 3.0, 4.0});

    // Create a figure.
    plotly_plotter::figure figure =
        plotly_plotter::figure_builders::scatter(data)
            .x("x")
            .y("y")
            // Set column name for colors of markers.
            .marker_color("Color")
            .title("Scatter Plot with Colorized Markers")
            .create();

    // Optionally tune the figure for better visualization.
    auto scatter_template = figure.add_scatter_template();
    scatter_template.marker().size(20);

    // Save the figure to a HTML file.
    plotly_plotter::write_html(
        "scatter_colorize_markers_in_figure_builder.html", figure);
}
