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
 * \brief Example to create a simple bar plot.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // Create a simple bar plot
    plotly_plotter::traces::bar bar = figure.add_bar();
    bar.x(std::vector{"A", "B", "C", "D", "E"});
    bar.y(std::vector{1, 2, 3, 4, 5});
    bar.name("Bar Plot");

    figure.title("Simple Bar Plot");
    plotly_plotter::write_html("bars_create_simple_bar.html", figure);
}
