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
 * \brief Example to use subplot_row function of a figure builder.
 */
#include <plotly_plotter/data_table.h>
#include <plotly_plotter/figure.h>
#include <plotly_plotter/figure_builders/line.h>
#include <plotly_plotter/write_html.h>

int main() {
    // Prepare data.
    plotly_plotter::data_table data;
    data.emplace("x", std::vector{1, 2, 3, 1, 2, 3});
    data.emplace("y", std::vector{1.2, 2.3, 3.4, 4.5, 5.6, 6.7});
    data.emplace("Group", std::vector{"A", "A", "A", "B", "B", "B"});

    // Create a figure.
    const plotly_plotter::figure figure =
        plotly_plotter::figure_builders::line(data)
            .x("x")
            .y("y")
            // Set grouping using subplot_row function.
            .subplot_row("Group")
            .title(
                "Example to Use <b>subplot_row</b> Function of a Figure "
                "Builder")
            .create();

    // Save the figure to a HTML file.
    plotly_plotter::write_html(
        "get_started_grouping_in_figure_builder_use_subplot_row.html", figure);
}
