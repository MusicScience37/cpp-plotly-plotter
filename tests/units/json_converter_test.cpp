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
 * \brief Test of specializations of json_converter class.
 */
#include "plotly_plotter/json_converter.h"  // IWYU pragma: keep

#include <string>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::json_converter<bool>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert true") {
        document.root() = true;

        CHECK(yyjson_mut_is_true(document.root().internal_value()));
    }

    SECTION("convert false") {
        document.root() = false;

        CHECK(yyjson_mut_is_false(document.root().internal_value()));
    }
}

TEST_CASE("plotly_plotter::json_converter<unsigned integer types>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert uint8_t") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = static_cast<uint8_t>(123);

        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK(yyjson_mut_get_uint(document.root().internal_value()) == 123);
    }

    SECTION("convert uint16_t") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = static_cast<uint16_t>(12345);

        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK(yyjson_mut_get_uint(document.root().internal_value()) == 12345);
    }

    SECTION("convert uint32_t") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = static_cast<uint32_t>(1234567890);

        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK(yyjson_mut_get_uint(document.root().internal_value()) ==
            1234567890);
    }

    SECTION("convert uint64_t") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = static_cast<uint64_t>(12345678901234567890ULL);

        CHECK(yyjson_mut_get_uint(document.root().internal_value()) ==
            // NOLINTNEXTLINE(*-magic-numbers)
            12345678901234567890ULL);
    }
}

TEST_CASE("plotly_plotter::json_converter<signed integer types>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert int8_t") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = static_cast<int8_t>(-123);

        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK(yyjson_mut_get_sint(document.root().internal_value()) == -123);
    }

    SECTION("convert int16_t") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = static_cast<int16_t>(-12345);

        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK(yyjson_mut_get_sint(document.root().internal_value()) == -12345);
    }

    SECTION("convert int32_t") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = static_cast<int32_t>(-1234567890);

        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK(yyjson_mut_get_sint(document.root().internal_value()) ==
            -1234567890);
    }

    SECTION("convert int64_t") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = static_cast<int64_t>(-1234567890123456789LL);

        CHECK(yyjson_mut_get_sint(document.root().internal_value()) ==
            // NOLINTNEXTLINE(*-magic-numbers)
            -1234567890123456789LL);
    }
}

TEST_CASE("plotly_plotter::json_converter<floating point types>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert float") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = 1.25F;

        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK(yyjson_mut_get_real(document.root().internal_value()) == 1.25);
    }

    SECTION("convert double") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = 1.25;

        // NOLINTNEXTLINE(*-magic-numbers)
        CHECK(yyjson_mut_get_real(document.root().internal_value()) == 1.25);
    }
}

TEST_CASE("plotly_plotter::json_converter<strings>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert std::string") {
        document.root() = std::string("abc");

        REQUIRE(yyjson_mut_is_str(document.root().internal_value()));
        CHECK(std::string(yyjson_mut_get_str(
                  document.root().internal_value())) == "abc");
    }

    SECTION("convert std::string_view") {
        document.root() = std::string_view("abc");

        REQUIRE(yyjson_mut_is_str(document.root().internal_value()));
        CHECK(std::string(yyjson_mut_get_str(
                  document.root().internal_value())) == "abc");
    }

    SECTION("convert C-style strings") {
        document.root() = "abc";

        REQUIRE(yyjson_mut_is_str(document.root().internal_value()));
        CHECK(std::string(yyjson_mut_get_str(
                  document.root().internal_value())) == "abc");
    }
}
