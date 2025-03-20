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
 * \brief Test of array_view class.
 */
#include "plotly_plotter/array_view.h"

#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <yyjson.h>

#include "plotly_plotter/json_document.h"
#include "plotly_plotter/json_value.h"

TEST_CASE("plotly_plotter::array_view") {
    using plotly_plotter::as_array;
    using plotly_plotter::json_document;
    using plotly_plotter::json_value;

    json_document document;
    json_value value = document.root();

    SECTION("convert std::vector to json_value") {
        value = as_array(std::vector{1, 2, 3});

        REQUIRE(yyjson_mut_is_arr(value.internal_value()));
        REQUIRE(yyjson_mut_arr_get(value.internal_value(), 0) != nullptr);
        CHECK(yyjson_mut_get_sint(
                  yyjson_mut_arr_get(value.internal_value(), 0)) == 1);
        REQUIRE(yyjson_mut_arr_get(value.internal_value(), 1) != nullptr);
        CHECK(yyjson_mut_get_sint(
                  yyjson_mut_arr_get(value.internal_value(), 1)) == 2);
        REQUIRE(yyjson_mut_arr_get(value.internal_value(), 2) != nullptr);
        CHECK(yyjson_mut_get_sint(
                  yyjson_mut_arr_get(value.internal_value(), 2)) == 3);
    }
}
