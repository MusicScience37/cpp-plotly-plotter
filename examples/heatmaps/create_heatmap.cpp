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
 * \brief Example to create a heatmap.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // Create a heatmap trace.
    plotly_plotter::traces::heatmap heatmap = figure.add_heatmap();
    heatmap.z(std::vector<std::vector<double>>{
        {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    heatmap.x(std::vector{1, 2, 3});
    heatmap.y(std::vector{1, 2, 3});
    heatmap.name("Heatmap");
    heatmap.color_axis("coloraxis");

    // Optionally configure color bar.
    figure.layout().color_axis().show_scale(true);
    figure.layout().color_axis().color_bar().title().text("Color Axis");
    figure.layout().color_axis().c_min(0.0);
    figure.layout().color_axis().c_max(10.0);

    // Optionally configure titles.
    figure.layout().xaxis().title().text("x");
    figure.layout().yaxis().title().text("y");
    figure.title("Heatmap Example");

    // Save the figure to an HTML file.
    plotly_plotter::write_html("heatmaps_create_heatmap.html", figure);
}
