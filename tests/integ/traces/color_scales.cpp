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
 * \brief Test of color scales.
 */
#include "plotly_plotter/color_scales.h"

#include <Eigen/Core>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include "plotly_plotter/eigen.h"  // IWYU pragma: keep
#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/heatmap.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("color scales") {
    plotly_plotter::figure figure;

    constexpr int num_points = 101;
    const Eigen::VectorXd values =
        Eigen::VectorXd::LinSpaced(num_points, 0.0, 1.0);
    const Eigen::VectorXd y = Eigen::VectorXd::Constant(num_points, 0.0);

    SECTION("builtin color scales") {
        const auto color_scales = std::vector<std::string_view>{"Blackbody",
            "Bluered", "Blues", "Cividis", "Earth", "Electric", "Greens",
            "Greys", "Hot", "Jet", "Picnic", "Portland", "Rainbow", "RdBu",
            "Reds", "Viridis", "YlGnBu", "YlOrRd"};

        for (std::size_t i = 0; i < color_scales.size(); ++i) {
            auto heatmap = figure.add_heatmap();
            heatmap.z(values);
            heatmap.x(values);
            heatmap.y(y);
            if (i > 0) {
                heatmap.yaxis(fmt::format("y{}", i + 1));
                heatmap.color_axis(fmt::format("coloraxis{}", i + 1));
            } else {
                heatmap.yaxis("y");
                heatmap.color_axis("coloraxis");
            }
            heatmap.xaxis("x");
            heatmap.z_smooth("best");
            heatmap.name(color_scales[i]);

            figure.layout().color_axis(i + 1).show_scale(false);
            figure.layout().color_axis(i + 1).color_scale(color_scales[i]);

            figure.layout().yaxis(i + 1).show_tick_labels(false);
            figure.layout().yaxis(i + 1).ticks("");
        }

        figure.layout().grid().rows(color_scales.size());
        figure.layout().grid().columns(1);
        figure.layout().grid().pattern("coupled");

        const std::string file_path = "color_scales_builtin.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("plotly_plotter color scales") {
        // NOLINTNEXTLINE(*-using-namespace)
        using namespace plotly_plotter::color_scales;

        const auto color_scales = std::vector<std::pair<std::string,
            std::vector<std::pair<double, std::string>>>>{{"gray", gray()},
            {"inverted_gray", inverted_gray()},
            {"cool_warm_simple", cool_warm_simple()},
            {"cool_warm_darker", cool_warm_darker()},
            {"cool_warm_extended", cool_warm_extended()},
            {"cool_warm_extended_relaxed", cool_warm_extended_relaxed()},
            {"cool_extended", cool_extended()},
            {"warm_extended", warm_extended()}, {"blown", blown()},
            {"autumn", autumn()}, {"autumn_full", autumn_full()},
            {"red", red()}, {"red_full", red_full()}, {"green", green()},
            {"green_full", green_full()}, {"blue", blue()},
            {"blue_full", blue_full()}, {"green_to_autumn", green_to_autumn()},
            {"green_to_autumn_on_yellow", green_to_autumn_on_yellow()},
            {"blue_to_autumn", blue_to_autumn()},
            {"blue_to_autumn_on_green", blue_to_autumn_on_green()},
            {"green_to_red", green_to_red()},
            {"green_to_red_on_yellow", green_to_red_on_yellow()},
            {"blue_to_red", blue_to_red()},
            {"blue_to_red_on_green", blue_to_red_on_green()},
            {"purple_green_yellow", purple_green_yellow()},
            {"blue_purple_red", blue_purple_red()},
            {"blue_green_red", blue_green_red()}, {"whole_hue", whole_hue()}};

        for (std::size_t i = 0; i < color_scales.size(); ++i) {
            auto heatmap = figure.add_heatmap();
            heatmap.z(values);
            heatmap.x(values);
            heatmap.y(y);
            if (i > 0) {
                heatmap.yaxis(fmt::format("y{}", i + 1));
                heatmap.color_axis(fmt::format("coloraxis{}", i + 1));
            } else {
                heatmap.yaxis("y");
                heatmap.color_axis("coloraxis");
            }
            heatmap.xaxis("x");
            heatmap.z_smooth("best");
            heatmap.name(color_scales[i].first);

            figure.layout().color_axis(i + 1).show_scale(false);
            figure.layout().color_axis(i + 1).color_scale(
                color_scales[i].second);

            figure.layout().yaxis(i + 1).show_tick_labels(false);
            figure.layout().yaxis(i + 1).ticks("");
        }

        figure.layout().grid().rows(color_scales.size());
        figure.layout().grid().columns(1);
        figure.layout().grid().pattern("coupled");

        const std::string file_path = "color_scales_plotly_plotter.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
