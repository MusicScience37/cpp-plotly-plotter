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
 * \brief Example to create a grouped scatter plot using traces.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // First group.
    plotly_plotter::traces::scatter scatter = figure.add_scatter();
    // Set x and y data.
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{1.2, 2.3, 3.4});
    // Set the name of the trace.
    scatter.name("A");
    // Additional configuration of plotly.js.
    scatter.hover_template("Group=A<br>x=%{x}<br>y=%{y}");
    scatter.mode("markers");

    // Second group.
    scatter = figure.add_scatter();
    // Set x and y data.
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{4.5, 5.6, 6.7});
    // Set the name of the trace.
    scatter.name("B");
    // Additional configuration of plotly.js.
    scatter.hover_template("Group=B<br>x=%{x}<br>y=%{y}");
    scatter.mode("markers");

    // Configure titles.
    figure.layout().xaxis().title().text("x");
    figure.layout().yaxis().title().text("y");
    figure.title("Scatter Plot");

    // Save the figure to a HTML file.
    plotly_plotter::write_html(
        "scatter_create_grouped_scatter_using_traces.html", figure);
}
