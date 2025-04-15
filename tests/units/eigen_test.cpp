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
 * \brief Test of classes to support Eigen library.
 */
#include "plotly_plotter/eigen.h"

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::json_converter<Eigen::Matrix>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert a column vector") {
        document.root() = Eigen::VectorXi{{1, 2, 3}};

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 3);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 0)) == 1);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 1)) == 2);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 2)) == 3);
    }

    SECTION("convert a row vector") {
        document.root() = Eigen::RowVectorXi{{1, 2, 3}};

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 3);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 0)) == 1);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 1)) == 2);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 2)) == 3);
    }

    SECTION("convert a matrix") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = Eigen::MatrixXi{{1, 2, 3}, {4, 5, 6}};

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 2);
        REQUIRE(yyjson_mut_is_arr(
            yyjson_mut_arr_get(document.root().internal_value(), 0)));
        REQUIRE(yyjson_mut_arr_size(yyjson_mut_arr_get(
                    document.root().internal_value(), 0)) == 3);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  yyjson_mut_arr_get(document.root().internal_value(), 0),
                  0)) == 1);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  yyjson_mut_arr_get(document.root().internal_value(), 0),
                  1)) == 2);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  yyjson_mut_arr_get(document.root().internal_value(), 0),
                  2)) == 3);
        REQUIRE(yyjson_mut_is_arr(
            yyjson_mut_arr_get(document.root().internal_value(), 1)));
        REQUIRE(yyjson_mut_arr_size(yyjson_mut_arr_get(
                    document.root().internal_value(), 1)) == 3);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  yyjson_mut_arr_get(document.root().internal_value(), 1),
                  0)) == 4);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  yyjson_mut_arr_get(document.root().internal_value(), 1),
                  1)) == 5);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  yyjson_mut_arr_get(document.root().internal_value(), 1),
                  2)) == 6);
    }
}
