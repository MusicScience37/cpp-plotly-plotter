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
 * \brief Test of calculate_histogram_bin_width function.
 */
#include "plotly_plotter/utils/calculate_histogram_bin_width.h"

#include <Eigen/Core>
#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE(
    "plotly_plotter::utils::calculate_histogram_bin_width_freedman_diaconis") {
    using plotly_plotter::utils::
        calculate_histogram_bin_width_freedman_diaconis;

    SECTION("calculate bin width for double values") {
        const auto input = std::vector<double>{1.0, 4.0, 2.0};

        const auto bin_width =
            calculate_histogram_bin_width_freedman_diaconis(input);

        const double expected_bin_width =
            2.0 * (3.0 - 1.5) * std::pow(3.0, -1.0 / 3.0);
        CHECK_THAT(bin_width, Catch::Matchers::WithinRel(expected_bin_width));
    }
}

TEST_CASE("plotly_plotter::utils::histogram_bin_width_method") {
    using plotly_plotter::utils::calculate_histogram_bin_width;
    using plotly_plotter::utils::histogram_bin_width_method;

    SECTION("use methods") {
        const auto input = std::vector<double>{1.0, 4.0, 2.0};

        SECTION("Freedman-Diaconis rule") {
            const auto bin_width = calculate_histogram_bin_width(
                input, histogram_bin_width_method::freedman_diaconis);

            const double expected_bin_width =
                2.0 * (3.0 - 1.5) * std::pow(3.0, -1.0 / 3.0);
            CHECK_THAT(
                bin_width, Catch::Matchers::WithinRel(expected_bin_width));
        }
    }

    SECTION("calculate for Eigen vectors") {
        const Eigen::VectorXd input{{1.0, 4.0, 2.0}};

        const auto bin_width = calculate_histogram_bin_width(input);

        const double expected_bin_width =
            2.0 * (3.0 - 1.5) * std::pow(3.0, -1.0 / 3.0);
        CHECK_THAT(bin_width, Catch::Matchers::WithinRel(expected_bin_width));
    }
}
