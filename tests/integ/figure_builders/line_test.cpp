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

#include <cstddef>
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

    SECTION("line with a group") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3, 1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6, 7, 8, 9});
        data.emplace(
            "group", std::vector<std::string>{"A", "A", "A", "B", "B", "B"});
        data.emplace(
            "hover", std::vector<std::string>{"a", "b", "c", "d", "e", "f"});

        SECTION("in groups") {
            const auto figure = line(data)
                                    .x("x")
                                    .y("y")
                                    .group("group")
                                    .hover_data({"hover"})
                                    .title("Line with Group")
                                    .create();

            const std::string file_path = "line_with_group_in_groups.html";
            write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in columns of subplots") {
            const auto figure = line(data)
                                    .x("x")
                                    .y("y")
                                    .subplot_column("group")
                                    .hover_data({"hover"})
                                    .title("Line with Group")
                                    .create();

            const std::string file_path =
                "line_with_group_in_columns_of_subplots.html";
            write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("line with two groups") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3});
        data.emplace(  // NOLINTNEXTLINE(*-magic-numbers)
            "y", std::vector<int>{4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
        data.emplace("group1",
            std::vector<std::string>{
                "A", "A", "A", "A", "A", "A", "B", "B", "B", "B", "B", "B"});
        data.emplace("group2",
            std::vector<std::string>{
                "C", "C", "C", "D", "D", "D", "C", "C", "C", "D", "D", "D"});
        data.emplace("hover",
            std::vector<std::string>{
                "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"});

        SECTION("in groups and columns") {
            const auto figure = line(data)
                                    .x("x")
                                    .y("y")
                                    .group("group1")
                                    .subplot_column("group2")
                                    .hover_data({"hover"})
                                    .title("Line with Two Groups")
                                    .create();

            const std::string file_path =
                "line_with_two_groups_in_groups_and_columns.html";
            write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("line with hover data") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6});
        data.emplace("hover", std::vector<std::string>{"A", "B", "C"});

        const auto figure = line(data)
                                .x("x")
                                .y("y")
                                .hover_data({"hover"})
                                .title("Line with Hover Data")
                                .create();
        const std::string file_path = "line_with_hover_data.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("line with many points") {
        constexpr std::size_t num_points = 10000;
        std::vector<double> x;
        std::vector<double> y;
        x.reserve(num_points);
        y.reserve(num_points);
        for (std::size_t i = 0; i < num_points; ++i) {
            const double x_value = static_cast<double>(i) / num_points;
            const double y_value = x_value * x_value;
            x.push_back(x_value);
            y.push_back(y_value);
        }

        data_table data;
        data.emplace("x", x);
        data.emplace("y", y);

        const auto figure =
            line(data).x("x").y("y").title("Line with Many Points").create();

        const std::string file_path = "line_with_many_points.html";
        write_html(file_path, figure);
        // This produces a large file, so we do not verify it with
        // ApprovalTests.
    }
}
