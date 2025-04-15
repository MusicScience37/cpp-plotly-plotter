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
 * \brief Test of heatmap class.
 */
#include "plotly_plotter/traces/heatmap.h"

#include <string>
#include <string_view>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::traces::heatmap") {
    plotly_plotter::figure figure;

    SECTION("set parameters") {
        auto heatmap = figure.add_heatmap();

        CHECK_NOTHROW(heatmap.name("heatmap1"));
        CHECK_NOTHROW(heatmap.x(std::vector{1, 2, 3}));
        CHECK_NOTHROW(
            heatmap.y(std::vector{4, 5, 6}));  // NOLINT(*-magic-numbers)
        CHECK_NOTHROW(heatmap.text(std::vector{"a", "b", "c"}));
        CHECK_NOTHROW(heatmap.xaxis("x"));
        CHECK_NOTHROW(heatmap.yaxis("y"));
        CHECK_NOTHROW(heatmap.hover_template(
            "x: %{x}<br>y: %{y}<br>z: %{z}<br>text: %{text}"));
        CHECK_NOTHROW(heatmap.legend_group("heatmap1"));
        CHECK_NOTHROW(heatmap.show_legend(true));
        CHECK_NOTHROW(heatmap.z(
            std::vector<std::vector<double>>{// NOLINTNEXTLINE(*-magic-numbers)
                {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}}));
        CHECK_NOTHROW(heatmap.color_axis("coloraxis"));
        CHECK_NOTHROW(heatmap.z_smooth("best"));

        const std::string json_string =
            figure.document().serialize_to_string(true);
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }
}
