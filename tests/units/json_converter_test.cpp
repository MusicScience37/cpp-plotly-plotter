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

#include <chrono>
#include <limits>
#include <string>
#include <string_view>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

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

    SECTION("convert NaN") {
        document.root() = std::numeric_limits<double>::quiet_NaN();

        CHECK(yyjson_mut_is_null(document.root().internal_value()));
    }

    SECTION("convert infinity") {
        document.root() = std::numeric_limits<double>::infinity();

        CHECK(yyjson_mut_is_null(document.root().internal_value()));
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

TEST_CASE("plotly_plotter::json_converter<std::vector<T>>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert std::vector<int>") {
        document.root() = std::vector<int>{1, 2, 3};

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 3);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 0)) == 1);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 1)) == 2);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 2)) == 3);
    }

    SECTION("convert std::vector<std::vector<int>>") {
        // NOLINTNEXTLINE(*-magic-numbers)
        document.root() = std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}};

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

TEST_CASE("plotly_plotter::json_converter<std::array<T, Size>>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert std::array<int, 3>") {
        document.root() = std::array<int, 3>{1, 2, 3};

        REQUIRE(yyjson_mut_is_arr(document.root().internal_value()));
        REQUIRE(yyjson_mut_arr_size(document.root().internal_value()) == 3);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 0)) == 1);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 1)) == 2);
        CHECK(yyjson_mut_get_sint(yyjson_mut_arr_get(
                  document.root().internal_value(), 2)) == 3);
    }
}

TEST_CASE("plotly_plotter::json_converter<std::timespec>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert") {
        // 2025-03-23 23:22:14.123456789 UTC
        const std::timespec time{
            1742772134, 123456789};  // NOLINT(*-magic-numbers)

        document.root() = time;

        REQUIRE(yyjson_mut_is_str(document.root().internal_value()));
        CHECK(
            std::string(yyjson_mut_get_str(document.root().internal_value())) ==
            "2025-03-23 23:22:14.123456789");
    }
}

TEST_CASE(
    "plotly_plotter::json_converter<std::chrono::system_clock::time_point>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert") {
        // 2025-03-23 23:22:14.123456789 UTC
        const std::chrono::system_clock::time_point time{
            std::chrono::duration_cast<std::chrono::system_clock::duration>(
                std::chrono::seconds{1742772134} +
                std::chrono::nanoseconds{
                    123456789})};  // NOLINT(*-magic-numbers)

        document.root() = time;

        REQUIRE(yyjson_mut_is_str(document.root().internal_value()));
        CHECK_THAT(
            std::string(yyjson_mut_get_str(document.root().internal_value())),
            // System clock may not use nanoseconds.
            Catch::Matchers::Matches(R"(2025-03-23 23:22:14.123\d\d\d\d\d\d)"));
    }
}

TEST_CASE("plotly_plotter::json_converter<std::nullptr_t>") {
    using plotly_plotter::json_document;

    json_document document;

    SECTION("convert") {
        document.root() = nullptr;

        CHECK(yyjson_mut_is_null(document.root().internal_value()));
    }
}
