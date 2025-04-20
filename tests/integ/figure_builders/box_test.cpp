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
 * \brief Test of box plots.
 */
#include "plotly_plotter/figure_builders/box.h"

#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("box") {
    using plotly_plotter::data_table;
    using plotly_plotter::write_html;
    using plotly_plotter::figure_builders::box;

    SECTION("simple box plot") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 5, 10});

        const auto figure = box(data).y("y").title("Simple Box").create();

        const std::string file_path = "box_simple_box_plot.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("box with a group") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{0, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        data.emplace("group",
            std::vector<std::string>{
                "A", "A", "A", "A", "A", "A", "B", "B", "B", "B"});
        data.emplace("hover",
            std::vector<std::string>{
                "a", "b", "c", "d", "e", "f", "g", "h", "i", "j"});

        SECTION("in x-axis") {
            const auto figure = box(data)
                                    .x("group")
                                    .y("y")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path = "box_with_group_in_x.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in group") {
            const auto figure = box(data)
                                    .y("y")
                                    .group("group")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path = "box_with_group_in_group.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in columns of subplots") {
            const auto figure = box(data)
                                    .y("y")
                                    .subplot_column("group")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "box_with_group_in_columns_of_subplots.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in rows of subplots") {
            const auto figure = box(data)
                                    .y("y")
                                    .subplot_row("group")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "box_with_group_in_rows_of_subplots.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in animation frames") {
            auto figure = box(data)
                              .y("y")
                              .animation_frame("group")
                              .box_mean("sd")
                              .box_points("all")
                              .hover_data({"hover"})
                              .title("Test Title")
                              .create();

            const std::string file_path =
                "box_with_group_in_animation_frames.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("box with two groups") {
        data_table data;
        data.emplace("y",
            // NOLINTNEXTLINE(*-magic-numbers)
            std::vector<int>{1, 2, 3, 5, 10, 2, 3, 4, 5, 11,
                // NOLINTNEXTLINE(*-magic-numbers)
                3, 4, 5, 6, 12, 4, 5, 6, 7, 13});
        data.emplace("group1",
            std::vector<std::string>{"A", "A", "A", "A", "A", "A", "A", "A",
                "A", "A", "B", "B", "B", "B", "B", "B", "B", "B", "B", "B"});
        data.emplace("group2",
            std::vector<std::string>{"C", "C", "C", "C", "C", "D", "D", "D",
                "D", "D", "C", "C", "C", "C", "C", "D", "D", "D", "D", "D"});
        data.emplace("hover",
            std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h",
                "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t"});

        SECTION("in x-axis and group") {
            const auto figure = box(data)
                                    .x("group1")
                                    .y("y")
                                    .group("group2")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "box_with_two_groups_in_x_and_group.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in x-axis and columns of subplots") {
            const auto figure = box(data)
                                    .x("group1")
                                    .y("y")
                                    .subplot_column("group2")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "box_with_two_groups_in_x_and_columns_of_subplots.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in x-axis and rows of subplots") {
            const auto figure = box(data)
                                    .x("group1")
                                    .y("y")
                                    .subplot_row("group2")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "box_with_two_groups_in_x_and_rows_of_subplots.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in group and columns of subplots") {
            const auto figure = box(data)
                                    .y("y")
                                    .group("group1")
                                    .subplot_column("group2")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "box_with_two_groups_in_group_and_columns_of_subplots.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in group and rows of subplots") {
            const auto figure = box(data)
                                    .y("y")
                                    .group("group1")
                                    .subplot_row("group2")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "box_with_two_groups_in_group_and_rows_of_subplots.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in columns and rows of subplots") {
            const auto figure = box(data)
                                    .y("y")
                                    .subplot_row("group1")
                                    .subplot_column("group2")
                                    .box_mean("sd")
                                    .box_points("all")
                                    .hover_data({"hover"})
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "box_with_two_groups_in_columns_and_rows_of_subplots.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("log scale") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 5, 50, 2, 3, 4, 10, 100});
        data.emplace("group",
            std::vector<std::string>{
                "A", "A", "A", "A", "A", "B", "B", "B", "B", "B"});

        const auto figure =
            box(data).y("y").group("group").log_y(true).create();

        const std::string file_path = "box_with_log_scale.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
