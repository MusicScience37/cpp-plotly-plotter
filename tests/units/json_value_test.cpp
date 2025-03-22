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
 * \brief Test of json_value class.
 */
#include "plotly_plotter/json_value.h"

#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/array_view.h"
#include "plotly_plotter/json_converter.h"  // IWYU pragma: keep
#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::json_value") {
    using plotly_plotter::json_document;

    SECTION("set a value") {
        json_document document;

        constexpr int value = 12345;
        document.root() = value;

        CHECK(yyjson_mut_get_int(document.root().internal_value()) == value);
    }

    SECTION("append a value as an array using push_back") {
        json_document document;

        document.root().push_back(123);  // NOLINT(*-magic-numbers)
        document.root().push_back("abc");

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 2);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(document.root().internal_value(), 0)));
        CHECK(yyjson_mut_get_int(yyjson_mut_arr_get(
                  // NOLINTNEXTLINE(*-magic-numbers)
                  document.root().internal_value(), 0)) == 123);
        REQUIRE(yyjson_mut_is_str(
            yyjson_mut_arr_get(document.root().internal_value(), 1)));
        CHECK(std::string(yyjson_mut_get_str(yyjson_mut_arr_get(
                  document.root().internal_value(), 1))) == "abc");
    }

    SECTION("append a value as an array using emplace_back") {
        json_document document;

        document.root().emplace_back() = 123;  // NOLINT(*-magic-numbers)
        document.root().emplace_back() = "abc";

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 2);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_arr_get(document.root().internal_value(), 0)));
        CHECK(yyjson_mut_get_int(yyjson_mut_arr_get(
                  // NOLINTNEXTLINE(*-magic-numbers)
                  document.root().internal_value(), 0)) == 123);
        REQUIRE(yyjson_mut_is_str(
            yyjson_mut_arr_get(document.root().internal_value(), 1)));
        CHECK(std::string(yyjson_mut_get_str(yyjson_mut_arr_get(
                  document.root().internal_value(), 1))) == "abc");
    }

    SECTION("set to an object") {
        json_document document;

        document.root()["key1"] = 123;  // NOLINT(*-magic-numbers)
        document.root()["key2"]["key3"] = "abc";

        REQUIRE(yyjson_mut_is_obj(document.root().internal_value()));
        REQUIRE(yyjson_mut_obj_size(document.root().internal_value()) == 2);
        REQUIRE(yyjson_mut_is_int(
            yyjson_mut_obj_get(document.root().internal_value(), "key1")));
        CHECK(yyjson_mut_get_int(yyjson_mut_obj_get(
                  // NOLINTNEXTLINE(*-magic-numbers)
                  document.root().internal_value(), "key1")) == 123);
        REQUIRE(yyjson_mut_is_obj(
            yyjson_mut_obj_get(document.root().internal_value(), "key2")));
        REQUIRE(yyjson_mut_obj_size(yyjson_mut_obj_get(
                    document.root().internal_value(), "key2")) == 1);
        REQUIRE(yyjson_mut_is_str(yyjson_mut_obj_get(
            yyjson_mut_obj_get(document.root().internal_value(), "key2"),
            "key3")));
        CHECK(std::string(yyjson_mut_get_str(yyjson_mut_obj_get(
                  yyjson_mut_obj_get(document.root().internal_value(), "key2"),
                  "key3"))) == "abc");
    }

    SECTION("try to change the type of a value from an array") {
        json_document document;

        document.root().push_back(123);  // NOLINT(*-magic-numbers)

        CHECK_THROWS_AS(document.root() = true, std::runtime_error);
        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK_THROWS_AS(document.root() = 123, std::runtime_error);
        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK_THROWS_AS(document.root() = 123U, std::runtime_error);
        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK_THROWS_AS(document.root() = 123.0, std::runtime_error);
        CHECK_THROWS_AS(
            document.root() = std::string("abc"), std::runtime_error);
        CHECK_THROWS_AS(document.root() = "abc", std::runtime_error);
        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK_THROWS_AS(document.root()["key"] = 123, std::runtime_error);
    }

    SECTION("try to change the type of a value from an object") {
        json_document document;

        document.root()["key"] = 123;  // NOLINT(*-magic-numbers)

        CHECK_THROWS_AS(document.root() = true, std::runtime_error);
        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK_THROWS_AS(document.root() = 123, std::runtime_error);
        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK_THROWS_AS(document.root() = 123U, std::runtime_error);
        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK_THROWS_AS(document.root() = 123.0, std::runtime_error);
        CHECK_THROWS_AS(
            document.root() = std::string("abc"), std::runtime_error);
        CHECK_THROWS_AS(document.root() = "abc", std::runtime_error);
        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK_THROWS_AS(document.root().push_back(123), std::runtime_error);
        CHECK_THROWS_AS(
            // NOLINTNEXTLINE(*-magic-numbers)
            document.root() = plotly_plotter::as_array(std::vector{123}),
            std::runtime_error);
    }

    SECTION("change the value") {
        json_document document;

        document.root() = "abc";
        document.root() = "def";

        REQUIRE(yyjson_mut_is_str(document.root().internal_value()));
        CHECK(std::string(yyjson_mut_get_str(
                  document.root().internal_value())) == "def");
    }
}
