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
 * \brief Test of has_iterator class.
 */
#include "plotly_plotter/details/has_iterator.h"

#include <array>
#include <vector>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("plotly_plotter::details::has_iterator_v") {
    using plotly_plotter::details::has_iterator_v;

    SECTION("check") {
        STATIC_REQUIRE(has_iterator_v<std::vector<int>>);
        STATIC_REQUIRE(has_iterator_v<std::vector<double>>);
        STATIC_REQUIRE(has_iterator_v<std::array<float, 3>>);
    }
}
