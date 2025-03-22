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
 * \brief Example to plot many points in scatter plots using WebGL.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // Prepare data.
    constexpr std::size_t num_points = 10000;
    std::vector<double> x_vec;
    std::vector<double> y_vec;
    x_vec.reserve(num_points);
    y_vec.reserve(num_points);
    for (std::size_t i = 0; i < num_points; ++i) {
        const double x =
            static_cast<double>(i) / static_cast<double>(num_points - 1);
        const double y = x * x;
        x_vec.push_back(x);
        y_vec.push_back(y);
    }

    // Create a scatter trace with many points.
    plotly_plotter::traces::scatter_gl scatter = figure.add_scatter_gl();
    scatter.x(x_vec);
    scatter.y(y_vec);
    scatter.mode("lines");
    scatter.name("$y=x^2$");

    figure.title("Scatter Plot with Many Points Using WebGL");
    plotly_plotter::write_html(
        "scatters_plot_many_points_using_web_gl.html", figure);
}
