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
 * \brief Test of line plots.
 */
#include "plotly_plotter/figure_builders/line.h"

#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("line") {
    using plotly_plotter::data_table;
    using plotly_plotter::write_html;
    using plotly_plotter::figure_builders::line;

    SECTION("simple line plot") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6});

        const auto figure =
            line(data).x("x").y("y").title("Simple Line").create();
        const std::string file_path = "line_simple_line_plot.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("line with group") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3, 1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6, 7, 8, 9});
        data.emplace(
            "group", std::vector<std::string>{"A", "A", "A", "B", "B", "B"});

        const auto figure = line(data)
                                .x("x")
                                .y("y")
                                .group("group")
                                .title("Line with Group")
                                .create();
        const std::string file_path = "line_with_group.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
