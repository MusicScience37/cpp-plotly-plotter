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
 * \brief Test of violin class.
 */
#include "plotly_plotter/traces/violin.h"

#include <string>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::traces::violin") {
    plotly_plotter::figure figure;

    SECTION("set parameters") {
        auto violin = figure.add_violin();

        CHECK_NOTHROW(violin.name("violin1"));
        CHECK_NOTHROW(violin.x(std::vector{1, 2, 3}));
        CHECK_NOTHROW(violin.y(std::vector{4, 5, 6}));
        CHECK_NOTHROW(violin.hover_template("x: %{x}<br>y: %{y}"));
        CHECK_NOTHROW(violin.legend_group("group1"));
        CHECK_NOTHROW(violin.box().visible(true));
        CHECK_NOTHROW(violin.mean_line().visible(true));
        CHECK_NOTHROW(violin.points("all"));

        const std::string json_string =
            figure.document().serialize_to_string(true);
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }
}
