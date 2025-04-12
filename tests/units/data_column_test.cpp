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
 * \brief Test of data_column class.
 */
#include "plotly_plotter/data_column.h"

#include <memory>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <yyjson.h>

#include "plotly_plotter/array_view.h"  // IWYU pragma: keep
#include "plotly_plotter/data_table.h"
#include "plotly_plotter/json_document.h"
#include "plotly_plotter/json_value.h"

TEST_CASE("plotly_plotter::data_column") {
    using plotly_plotter::data_table;
    using plotly_plotter::filter_data_column;
    using plotly_plotter::json_document;

    SECTION("convert all data to JSON") {
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

    SECTION("convert all data to JSON via assignment") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 3});

        json_document document;
        document.root() = *table.at("key1");

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

    SECTION("convert a part of data to JSON") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 3});

        json_document document;
        table.at("key1")->to_json_partial(document.root(), {true, false, true});

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 2);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(document.root().internal_value(), 0)));
        CHECK(yyjson_mut_get_int(yyjson_mut_arr_get(
                  document.root().internal_value(), 0)) == 1);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(document.root().internal_value(), 1)));
        CHECK(yyjson_mut_get_int(yyjson_mut_arr_get(
                  document.root().internal_value(), 1)) == 3);
    }

    SECTION("convert a part of data to JSON via assignment") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 3});

        json_document document;
        document.root() = filter_data_column(
            *table.at("key1"), std::vector{true, false, true});

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 2);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(document.root().internal_value(), 0)));
        CHECK(yyjson_mut_get_int(yyjson_mut_arr_get(
                  document.root().internal_value(), 0)) == 1);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(document.root().internal_value(), 1)));
        CHECK(yyjson_mut_get_int(yyjson_mut_arr_get(
                  document.root().internal_value(), 1)) == 3);
    }

    SECTION("generate groups") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 1, 3, 2});

        const auto [groups, indices] = table.at("key1")->generate_group();

        CHECK(groups == std::vector<std::string>{"1", "2", "3"});
        CHECK(indices == std::vector<std::size_t>{0, 1, 0, 2, 1});
    }

    SECTION("get the range in positive") {
        data_table table;
        table.emplace("key1", std::vector{1, 2, 0, -1, 3});

        const auto [min, max] = table.at("key1")->get_positive_range();

        CHECK(min == 1.0);  // NOLINT(*-magic-numbers)
        CHECK(max == 3.0);  // NOLINT(*-magic-numbers)
    }

    SECTION("try to get the range in positive for strings") {
        data_table table;
        table.emplace("key1", std::vector{"a", "b", "c"});

        CHECK_THROWS(table.at("key1")->get_positive_range());
    }
}
