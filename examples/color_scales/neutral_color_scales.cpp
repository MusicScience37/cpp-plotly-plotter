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
 * \brief Program to show neutral color scales in plotly_plotter library.
 */
#include <cmath>
#include <vector>

#include <fmt/format.h>
#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

#include "plotly_plotter/color_scales.h"

int main() {
    // Prepare data.
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

    // Prepare color scales.
    // NOLINTNEXTLINE(*-using-namespace)
    using namespace plotly_plotter::color_scales;
    const auto color_scales = std::vector<
        std::pair<std::string, std::vector<std::pair<double, std::string>>>>{
        {"autumn", autumn()}, {"red", red()}, {"green", green()},
        {"blue", blue()}, {"blown", blown()},
        {"purple_green_yellow", purple_green_yellow()}, {"tea", tea()},
        {"blue_purple_red", blue_purple_red()}};

    // Create the figure.
    plotly_plotter::figure figure;
    for (std::size_t i = 0; i < color_scales.size(); ++i) {
        auto heatmap = figure.add_heatmap();
        heatmap.z(z);
        heatmap.x(x);
        heatmap.y(y);
        if (i > 0) {
            heatmap.xaxis(fmt::format("x{}", i + 1));
            heatmap.yaxis(fmt::format("y{}", i + 1));
            heatmap.color_axis(fmt::format("coloraxis{}", i + 1));
        } else {
            heatmap.xaxis("x");
            heatmap.yaxis("y");
            heatmap.color_axis("coloraxis");
        }
        heatmap.z_smooth("best");
        heatmap.name(color_scales[i].first);

        figure.layout().color_axis(i + 1).show_scale(false);
        figure.layout().color_axis(i + 1).color_scale(color_scales[i].second);

        auto annotation = figure.layout().add_annotation();
        annotation.text(color_scales[i].first);
        if (i > 0) {
            annotation.x_ref(fmt::format("x{} domain", i + 1));
            annotation.y_ref(fmt::format("y{} domain", i + 1));
        } else {
            annotation.x_ref("x domain");
            annotation.y_ref("y domain");
        }
        annotation.x(0.5);
        annotation.y(1.0);
        annotation.y_shift(20.0);
        annotation.show_arrow(false);
    }

    figure.layout().grid().rows(4);
    figure.layout().grid().columns(2);
    figure.layout().grid().pattern("independent");

    figure.title("Neutral Color Scales in cpp-plotly-plotter");

    // Save the figure to an HTML file.
    plotly_plotter::write_html(
        "color_scales_neutral_color_scales.html", figure);
}
