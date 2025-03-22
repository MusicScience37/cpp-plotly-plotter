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
 * \brief Example to customize hover texts in a plot.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // Create a scatter trace with a hover template.
    plotly_plotter::traces::scatter scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{1.2, 2.3, 3.4});
    scatter.name("Scatter1");
    // Set the hover template of the scatter using hover_template function.
    scatter.hover_template("x: %{x}<br>y: %{y}");

    // Add another scatter trace with a hover template including texts.
    scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{2.3, 3.4, 4.5});
    scatter.text(std::vector{"A", "B", "C"});
    scatter.name("Scatter2");
    scatter.hover_template("x: %{x}<br>y: %{y}<br>text: %{text}");

    // Add another scatter trace with a hover template with formatting of
    // values.
    scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{3.4, 4.5, 5.6});
    scatter.name("Scatter3");
    scatter.hover_template("x: %{x}<br>y: %{y:.2f}");

    figure.title("Scatter Plots with Configuration of Hover Texts");
    plotly_plotter::write_html(
        "configurations_customize_hover_texts.html", figure);
}
