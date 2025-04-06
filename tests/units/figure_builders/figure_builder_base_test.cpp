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
 * \brief Test of figure_builder_base class.
 */
#include <string>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure_builders/line.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("plotly_plotter::figure_builders::figure_builder_base") {
    // figure_builder_base is an abstract class, so we use line class for
    // testing.

    using plotly_plotter::data_table;
    using plotly_plotter::figure_builders::line;

    SECTION("build with minimal settings") {
        data_table data;
        data.emplace("y", std::vector<int>{1, 2, 3});

        const auto figure = line(data).y("y").create();

        const std::string file_path =
            "figure_builder_base_with_minimal_settings.html";
        plotly_plotter::write_html(file_path, figure);
        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build without grouping") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6});

        const auto figure =
            line(data).x("x").y("y").title("Test Title").create();

        const std::string file_path =
            "figure_builder_base_build_without_grouping.html";
        plotly_plotter::write_html(file_path, figure);
        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with full settings") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3, 1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6, 7, 8, 9});
        data.emplace(
            "group", std::vector<std::string>{"A", "A", "A", "B", "B", "B"});
        data.emplace("additional1",
            std::vector<std::string>{"a", "b", "c", "d", "e", "f"});
        data.emplace("additional2",
            std::vector<std::string>{"x", "y", "z", "u", "v", "w"});

        const auto figure = line(data)
                                .x("x")
                                .y("y")
                                .group("group")
                                .hover_data({"additional1", "additional2"})
                                .title("Test Title")
                                .create();

        const std::string file_path =
            "figure_builder_base_build_with_full_settings.html";
        plotly_plotter::write_html(file_path, figure);
        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("try to create a figure with an inconsistent number of rows") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6});
        data.emplace("group", std::vector<std::string>{"A", "A"});

        // This should throw event when the inconsistent column is not used.
        CHECK_THROWS(line(data).x("x").y("y").create());
        CHECK_THROWS(line(data).y("y").create());
    }
}
