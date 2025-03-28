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
 * \brief Test of figure class.
 */
#include "plotly_plotter/figure.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("plotly_plotter::figure") {
    plotly_plotter::figure figure;

    SECTION("set title") {
        figure.title("Test Title");

        const std::string json_string = figure.document().serialize_to_string();
        CHECK(json_string ==
            R"({"data":[],"layout":{"title":{"text":"Test Title"}},"config":{"scrollZoom":true,"responsive":true}})");
        CHECK(figure.html_title() == "Test Title");
    }
}
