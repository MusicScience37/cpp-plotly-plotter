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
 * \brief Test of escape_for_html function.
 */
#include "plotly_plotter/details/escape_for_html.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("plotly_plotter::details::escape_for_html") {
    using plotly_plotter::details::escape_for_html;

    SECTION("escape strings") {
        CHECK(escape_for_html("abc") == "abc");
        CHECK(escape_for_html("a&b") == "a&amp;b");
        CHECK(escape_for_html("a<b") == "a&lt;b");
        CHECK(escape_for_html("a>b") == "a&gt;b");
        CHECK(escape_for_html("a\"b") == "a&quot;b");
        CHECK(escape_for_html("a'b") == "a&#x27;b");
    }
}
