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
 * \brief Test of to_string function.
 */
#include "plotly_plotter/to_string.h"

#include <chrono>
#include <string>
#include <string_view>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("plotly_plotter::to_string") {
    using plotly_plotter::to_string;

    SECTION("convert bool") {
        CHECK(to_string(true) == "true");
        CHECK(to_string(false) == "false");
    }

    SECTION("convert integers") {
        CHECK(to_string(123) == "123");    // NOLINT(*-magic-numbers)
        CHECK(to_string(-123) == "-123");  // NOLINT(*-magic-numbers)
        CHECK(to_string(123U) == "123");   // NOLINT(*-magic-numbers)
    }

    SECTION("convert floating-point numbers") {
        CHECK(to_string(123.456) == "123.456");    // NOLINT(*-magic-numbers)
        CHECK(to_string(-123.456) == "-123.456");  // NOLINT(*-magic-numbers)
        CHECK(to_string(123.456F) == "123.456");   // NOLINT(*-magic-numbers)
    }

    SECTION("convert std::string") {
        CHECK(to_string(std::string("abc")) == "abc");
    }

    SECTION("convert std::string_view") {
        CHECK(to_string(std::string_view("abc")) == "abc");
    }

    SECTION("convert std::timespec") {
        // 2025-03-23 23:22:14.123456789 UTC
        const std::timespec time{
            1742772134, 123456789};  // NOLINT(*-magic-numbers)

        CHECK(to_string(time) == "2025-03-23 23:22:14.123456789");
    }

    SECTION("convert std::chrono::system_clock::time_point") {
        // 2025-03-23 23:22:14.123456789 UTC
        const std::chrono::system_clock::time_point time{
            std::chrono::duration_cast<std::chrono::system_clock::duration>(
                std::chrono::seconds{1742772134} +
                std::chrono::nanoseconds{
                    123456789})};  // NOLINT(*-magic-numbers)

        CHECK_THAT(to_string(time),
            // System clock may not use nanoseconds.
            Catch::Matchers::Matches(R"(2025-03-23 23:22:14.123\d\d\d\d\d\d)"));
    }
}
