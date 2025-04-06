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
 * \brief Example to create a simple plot.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    // Create a figure.
    plotly_plotter::figure figure;

    // Create a scatter trace.
    plotly_plotter::traces::scatter scatter = figure.add_scatter();
    // Set x and y values.
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{1.2, 2.3, 3.4});

    // Save the figure to a HTML file.
    plotly_plotter::write_html("simple_plot.html", figure);
}
