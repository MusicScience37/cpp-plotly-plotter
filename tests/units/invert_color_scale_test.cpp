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
 * \brief Test of invert_color_scale function.
 */
#include "plotly_plotter/invert_color_scale.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("plotly_plotter::invert_color_scale") {
    using plotly_plotter::invert_color_scale;

    SECTION("invert an color scale") {
        const auto origin = std::vector<std::pair<double, std::string>>{
            {0.0, "#000000"}, {0.4, "#505050"}, {1.0, "#FFFFFF"}};

        const auto inverted = invert_color_scale(origin);

        const auto expected = std::vector<std::pair<double, std::string>>{
            {0.0, "#FFFFFF"}, {0.6, "#505050"}, {1.0, "#000000"}};
        CHECK(inverted == expected);
    }
}
