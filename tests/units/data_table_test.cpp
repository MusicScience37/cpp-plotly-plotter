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

#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <yyjson.h>

#include "plotly_plotter/array_view.h"  // IWYU pragma: keep
#include "plotly_plotter/json_document.h"
#include "plotly_plotter/json_value.h"

TEST_CASE("plotly_plotter::data_table") {
    using plotly_plotter::data_table;
    using plotly_plotter::json_document;

    SECTION("append columns using emplace function") {
        data_table table;

        table.emplace("key1", std::vector{1, 2, 3});

        json_document document;
        table.at("key1")->to_json(document.root());
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

    SECTION("append columns using emplace function with push_back") {
        data_table table;

        auto column1 = table.emplace<std::string>("key1");
        column1->push_back("a");
        column1->push_back("b");
        column1->push_back("c");

        json_document document;
        document.root() = *table.at("key1");
        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 3);
        REQUIRE(yyjson_mut_is_str(
            yyjson_mut_arr_get(document.root().internal_value(), 0)));
        CHECK(yyjson_mut_get_str(yyjson_mut_arr_get(
                  document.root().internal_value(), 0)) == std::string("a"));
        REQUIRE(yyjson_mut_is_str(
            yyjson_mut_arr_get(document.root().internal_value(), 1)));
        CHECK(yyjson_mut_get_str(yyjson_mut_arr_get(
                  document.root().internal_value(), 1)) == std::string("b"));
        REQUIRE(yyjson_mut_is_str(
            yyjson_mut_arr_get(document.root().internal_value(), 2)));
        CHECK(yyjson_mut_get_str(yyjson_mut_arr_get(
                  document.root().internal_value(), 2)) == std::string("c"));
    }

    SECTION("try to get a non-existing column using at function") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 3});
        table.emplace("key2", std::vector{"a", "b", "c"});

        CHECK_THROWS(table.at("key3"));
    }

    SECTION("check the number of rows") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 3});
        table.emplace("key2", std::vector{"a", "b", "c"});

        CHECK(table.has_consistent_rows());
        CHECK(table.rows() == 3);
    }

    SECTION("check the number of rows with empty table") {
        data_table table;

        CHECK(table.has_consistent_rows());
        CHECK(table.rows() == 0);
    }

    SECTION("check the number of rows with inconsistent columns") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 3});
        table.emplace("key2", std::vector{"a", "b"});

        CHECK_FALSE(table.has_consistent_rows());
    }
}
