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
 * \brief Example to select modes of scatter plots.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // Create a scatter trace with a mode.
    plotly_plotter::traces::scatter scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{1.2, 2.3, 3.4});
    scatter.name("lines");
    // Set the mode of the scatter using mode function.
    scatter.mode("lines");

    // Add another scatter trace with a different mode.
    scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{2.3, 3.4, 4.5});
    scatter.name("markers");
    scatter.mode("markers");

    // Add another scatter trace with a different mode.
    scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{3.4, 4.5, 5.6});
    scatter.name("lines+markers");
    scatter.mode("lines+markers");

    //! Add another scatter trace with a different mode.
    scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{4.5, 5.6, 6.7});
    scatter.text(std::vector{"A", "B", "C"});
    scatter.name("text");
    scatter.mode("text");

    figure.title("Scatter Plots with Different Modes");
    plotly_plotter::write_html("scatter_select_modes.html", figure);
}
