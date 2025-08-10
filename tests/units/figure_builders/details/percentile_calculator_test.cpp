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
 * \brief Test of percentile_calculator class.
 */
#include "plotly_plotter/figure_builders/details/percentile_calculator.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("plotly_plotter::figure_builders::details::percentile_calculator") {
    using plotly_plotter::figure_builders::details::percentile_calculator;

    SECTION("calculate percentiles of double values") {
        const auto input = std::vector<double>{1.0, 4.0, 2.0};
        const percentile_calculator<double> calculator(input);

        CHECK_THAT(  // NOLINTNEXTLINE(*-magic-numbers)
            calculator.percentile(0.0), Catch::Matchers::WithinRel(1.0));
        CHECK_THAT(  // NOLINTNEXTLINE(*-magic-numbers)
            calculator.percentile(0.25), Catch::Matchers::WithinRel(1.5));
        CHECK_THAT(  // NOLINTNEXTLINE(*-magic-numbers)
            calculator.percentile(0.5), Catch::Matchers::WithinRel(2.0));
        CHECK_THAT(  // NOLINTNEXTLINE(*-magic-numbers)
            calculator.percentile(0.75), Catch::Matchers::WithinRel(3.0));
        CHECK_THAT(  // NOLINTNEXTLINE(*-magic-numbers)
            calculator.percentile(0.8), Catch::Matchers::WithinRel(3.2));
        CHECK_THAT(  // NOLINTNEXTLINE(*-magic-numbers)
            calculator.percentile(1.0), Catch::Matchers::WithinRel(4.0));
    }
}
