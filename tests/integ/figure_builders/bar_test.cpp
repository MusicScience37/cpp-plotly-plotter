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
 * \brief Test of bar plots.
 */
#include "plotly_plotter/figure_builders/bar.h"

#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("bar") {
    using plotly_plotter::data_table;
    using plotly_plotter::write_html;
    using plotly_plotter::figure_builders::bar;

    SECTION("simple bar plot") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("x", std::vector<int>{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6});

        const auto figure =
            bar(data).x("x").y("y").title("Simple Bar").create();
        const std::string file_path = "bar_simple_bar_plot.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("bar with a group") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("x", std::vector<int>{1, 2, 3, 1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6, 7, 8, 9});
        data.emplace(
            "group", std::vector<std::string>{"A", "A", "A", "B", "B", "B"});
        data.emplace(
            "hover", std::vector<std::string>{"a", "b", "c", "d", "e", "f"});

        SECTION("in group") {
            const auto figure = bar(data)
                                    .x("x")
                                    .y("y")
                                    .hover_data({"hover"})
                                    .group("group")
                                    .title("Bar with Group in Group")
                                    .create();
            const std::string file_path = "bar_with_group_in_group.html";
            write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in columns of subplots") {
            const auto figure =
                bar(data)
                    .x("x")
                    .y("y")
                    .hover_data({"hover"})
                    .subplot_column("group")
                    .title("Bar with Group in Columns of Subplots")
                    .create();
            const std::string file_path =
                "bar_with_group_in_columns_of_subplots.html";
            write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in rows of subplots") {
            const auto figure = bar(data)
                                    .x("x")
                                    .y("y")
                                    .hover_data({"hover"})
                                    .subplot_row("group")
                                    .title("Bar with Group in Rows of Subplots")
                                    .create();
            const std::string file_path =
                "bar_with_group_in_rows_of_subplots.html";
            write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in animation frames") {
            const auto figure = bar(data)
                                    .x("x")
                                    .y("y")
                                    .hover_data({"hover"})
                                    .animation_frame("group")
                                    .title("Bar with Group in Animation Frames")
                                    .create();
            const std::string file_path =
                "bar_with_group_in_animation_frames.html";
            write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("log scale") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("x", std::vector<int>{1, 3, 10, 1, 3, 10});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6, 7, 8, 9});
        data.emplace(
            "group", std::vector<std::string>{"A", "A", "A", "B", "B", "B"});
        data.emplace(
            "hover", std::vector<std::string>{"a", "b", "c", "d", "e", "f"});

        const auto figure = bar(data)
                                .x("x")
                                .y("y")
                                .group("group")
                                .hover_data({"hover"})
                                .log_x(true)
                                .log_y(true)
                                .title("Bar with Log Scale")
                                .create();
        const std::string file_path = "bar_with_log_scale.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
