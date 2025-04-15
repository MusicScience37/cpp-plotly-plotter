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
}
