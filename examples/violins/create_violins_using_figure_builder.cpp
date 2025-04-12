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
 * \brief Example to create violin plots using figure builders.
 */
#include <plotly_plotter/data_table.h>
#include <plotly_plotter/figure.h>
#include <plotly_plotter/figure_builders/violin.h>
#include <plotly_plotter/write_html.h>

int main() {
    // Prepare data.
    plotly_plotter::data_table data;
    data.emplace("group",
        std::vector<std::string>{
            "A", "A", "A", "A", "A", "B", "B", "B", "B", "B"});
    data.emplace("y", std::vector<int>{1, 2, 3, 4, 10, 2, 3, 4, 5, 11});

    // Create a figure.
    const plotly_plotter::figure figure =
        plotly_plotter::figure_builders::violin(data)
            // Set y.
            .y("y")
            // Optionally set grouping of violins.
            .group("group")
            // Optionally set the title.
            .title("Violin Plot")
            .create();

    // Save the figure to a HTML file.
    plotly_plotter::write_html(
        "violins_create_violins_using_figure_builder.html", figure);
}
