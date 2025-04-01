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
 * \brief Test of data_table class.
 */
#include "plotly_plotter/data_table.h"

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/array_view.h"  // IWYU pragma: keep
#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::data_table") {
    using plotly_plotter::data_table;

    SECTION("append columns using emplace function") {
        data_table table;

        table.emplace("key1", std::vector{1, 2, 3});
        table.emplace("key2", std::vector{"a", "b", "c"});

        const auto json_string = table.data().serialize_to_string(true);
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }

    SECTION("append columns using operator[]") {
        data_table table;

        table["key1"].push_back(1);
        table["key1"].push_back(2);
        table["key1"].push_back(3);
        table["key2"].push_back("a");
        table["key2"].push_back("b");
        table["key2"].push_back("c");

        const auto json_string = table.data().serialize_to_string(true);
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }

    SECTION("get a column using at function") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 3});
        table.emplace("key2", std::vector{"a", "b", "c"});

        const auto column = table.at("key1");
        REQUIRE(yyjson_mut_is_arr(column.data().internal_value()));
        REQUIRE(yyjson_mut_arr_size(column.data().internal_value()) == 3);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(column.data().internal_value(), 0)));
        CHECK(yyjson_mut_get_int(
                  yyjson_mut_arr_get(column.data().internal_value(), 0)) == 1);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(column.data().internal_value(), 1)));
        CHECK(yyjson_mut_get_int(
                  yyjson_mut_arr_get(column.data().internal_value(), 1)) == 2);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(column.data().internal_value(), 2)));
        CHECK(yyjson_mut_get_int(
                  yyjson_mut_arr_get(column.data().internal_value(), 2)) == 3);

        CHECK_THROWS(table.at("key3"));
    }

    SECTION("copy a column to a JSON value") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 3});

        plotly_plotter::json_document document;
        document.root() = plotly_plotter::as_array(table.at("key1"));

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 3);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(document.root().internal_value(), 0)));
        CHECK(yyjson_mut_get_int(yyjson_mut_arr_get(
                  document.root().internal_value(), 0)) == 1);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(document.root().internal_value(), 1)));
        CHECK(yyjson_mut_get_int(yyjson_mut_arr_get(
                  document.root().internal_value(), 1)) == 2);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(document.root().internal_value(), 2)));
        CHECK(yyjson_mut_get_int(yyjson_mut_arr_get(
                  document.root().internal_value(), 2)) == 3);
    }
}
