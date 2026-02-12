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
 * \brief Example to invert a color scale.
 */
#include "plotly_plotter/invert_color_scale.h"

#include <cmath>
#include <vector>

#include <fmt/format.h>
#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

#include "plotly_plotter/color_scales.h"

int main() {
    // Prepare data for this example.
    constexpr double min_x = 0.0;
    constexpr double max_x = 1.0;
    constexpr double min_y = 0.0;
    constexpr double max_y = 1.0;
    constexpr int n_points_per_axis = 40;
    std::vector<double> x;
    std::vector<double> y;
    x.reserve(n_points_per_axis + 1);
    y.reserve(n_points_per_axis + 1);
    for (int i = 0; i <= n_points_per_axis; ++i) {
        x.push_back(min_x + (max_x - min_x) * i / n_points_per_axis);
        y.push_back(min_y + (max_y - min_y) * i / n_points_per_axis);
    }
    std::vector<std::vector<double>> z;
    z.resize(n_points_per_axis);
    for (std::size_t row = 0; row < n_points_per_axis; ++row) {
        z[row].resize(n_points_per_axis);
        for (std::size_t col = 0; col < n_points_per_axis; ++col) {
            constexpr double coeff = 5.0;
            z[row][col] = -0.8 *
                    std::exp(-coeff *
                        (std::pow(x[col] - 0.8, 2) +
                            std::pow(y[row] - 0.2, 2))) +
                std::exp(-coeff *
                    (std::pow(x[col] - 0.2, 2) + std::pow(y[row] - 0.8, 2)));
        }
    }

    // Create the figure.
    plotly_plotter::figure figure;
    auto heatmap = figure.add_heatmap();
    heatmap.z(z);
    heatmap.x(x);
    heatmap.y(y);
    heatmap.z_smooth("best");
    heatmap.color_axis("coloraxis");
    figure.layout().color_axis().show_scale(true);
    // Set the color scale here with inversion.
    figure.layout().color_axis().color_scale(plotly_plotter::invert_color_scale(
        plotly_plotter::color_scales::tea()));

    plotly_plotter::write_html("color_scales_invert_color_scale.html", figure);
}
