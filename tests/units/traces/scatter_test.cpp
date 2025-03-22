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
 * \brief Test of scatter class.
 */
#include "plotly_plotter/traces/scatter.h"

#include <string>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::traces::scatter") {
    plotly_plotter::figure figure;

    SECTION("set parameters") {
        auto scatter = figure.add_scatter();

        CHECK_NOTHROW(scatter.name("scatter1"));
        CHECK_NOTHROW(scatter.x(std::vector{1, 2, 3}));
        CHECK_NOTHROW(scatter.y(std::vector{4, 5, 6}));
        CHECK_NOTHROW(scatter.error_x().type("data"));
        CHECK_NOTHROW(scatter.error_x().symmetric(false));
        CHECK_NOTHROW(scatter.error_x().visible(true));
        CHECK_NOTHROW(scatter.error_x().array(
            std::vector{0.125, 0.25, 0.375}));  // NOLINT(*-magic-numbers)
        CHECK_NOTHROW(scatter.error_x().array_minus(
            std::vector{0.25, 0.5, 0.75}));  // NOLINT(*-magic-numbers)
        CHECK_NOTHROW(scatter.error_y().type("data"));
        CHECK_NOTHROW(scatter.error_y().symmetric(false));
        CHECK_NOTHROW(scatter.error_y().visible(true));
        CHECK_NOTHROW(scatter.error_y().array(
            std::vector{0.125, 0.25, 0.375}));  // NOLINT(*-magic-numbers)
        CHECK_NOTHROW(scatter.error_y().array_minus(
            std::vector{0.25, 0.5, 0.75}));  // NOLINT(*-magic-numbers)
        CHECK_NOTHROW(scatter.text(std::vector{"a", "b", "c"}));
        CHECK_NOTHROW(scatter.mode("lines"));
        CHECK_NOTHROW(
            scatter.hover_template("x: %{x}<br>y: %{y}<br>text: %{text}"));

        const std::string json_string =
            figure.document().serialize_to_string(true);
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }
}
