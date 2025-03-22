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
 * \brief Test of layout class.
 */
#include "plotly_plotter/layout.h"

#include <string>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::layout") {
    plotly_plotter::figure figure;

    SECTION("set parameters") {
        figure.layout().xaxis().title().text("x-axis");
        figure.layout().yaxis().title().text("y-axis");
        figure.layout().title().text("Test Title");

        const std::string json_string =
            figure.document().serialize_to_string(true);
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }
}
