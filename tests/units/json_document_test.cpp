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
 * \brief Test of json_document class.
 */
#include "plotly_plotter/json_document.h"

#include <cstdio>
#include <string_view>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: keep
#include "plotly_plotter/json_value.h"

TEST_CASE("plotly_plotter::json_document") {
    using plotly_plotter::json_document;
    using plotly_plotter::json_value;

    // TODO test of copy and move

    SECTION("serialize to JSON string") {
        json_document document;
        document.root()["key1"] = 123;  // NOLINT(*-magic-numbers)
        json_value array = document.root()["key2"];
        array.push_back("abc");
        array.emplace_back()["key3"] = 1.25;  // NOLINT(*-magic-numbers)

        const std::string result = document.serialize_to_string();

        ApprovalTests::Approvals::verify(result);
    }

    SECTION("serialize to a file") {
        json_document document;
        document.root()["key1"] = 123;  // NOLINT(*-magic-numbers)
        json_value array = document.root()["key2"];
        array.push_back("abc");
        array.emplace_back()["key3"] = 1.25;  // NOLINT(*-magic-numbers)

        const std::string file_path =
            "json_document_test_serialize_to_file.json";
        std::FILE* file = std::fopen(file_path.c_str(), "w");
        REQUIRE(file != nullptr);
        document.serialize_to(file);
        (void)std::fclose(file);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path));
    }
}
