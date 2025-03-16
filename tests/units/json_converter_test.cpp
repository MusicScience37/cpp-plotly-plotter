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

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/json_document.h"
#include "plotly_plotter/json_value.h"

TEST_CASE("plotly_plotter::json_converter<bool>") {
    using plotly_plotter::json_document;
    using plotly_plotter::json_value;

    json_document document;
    json_value value = document.root();

    SECTION("convert true") {
        value = true;

        CHECK(yyjson_mut_is_true(value.internal_value()));
    }

    SECTION("convert false") {
        value = false;

        CHECK(yyjson_mut_is_false(value.internal_value()));
    }
}
