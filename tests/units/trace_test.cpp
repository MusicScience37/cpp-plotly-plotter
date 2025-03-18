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
 * \brief Test of trace class.
 */
#include "plotly_plotter/trace.h"

#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"

TEST_CASE("plotly_plotter::trace") {
    plotly_plotter::figure figure;

    SECTION("set parameters") {
        auto trace = figure.add_trace();

        CHECK_NOTHROW(trace.type("scatter"));
        CHECK_NOTHROW(trace.name("trace1"));
        CHECK_NOTHROW(trace.x(std::vector{1, 2, 3}));
        CHECK_NOTHROW(trace.y(std::vector{4, 5, 6}));

        const std::string json_string = figure.document().serialize_to_string();
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }
}
