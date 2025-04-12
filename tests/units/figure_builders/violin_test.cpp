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
 * \brief Test of violin class.
 */
#include "plotly_plotter/figure_builders/violin.h"

#include <utility>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("plotly_plotter::figure_builders::violin") {
    using plotly_plotter::data_table;
    using plotly_plotter::figure_builders::violin;

    SECTION("build with minimal settings") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 5, 10});

        const auto figure = violin(data).y("y").create();

        const std::string file_path = "violin_build_with_minimal_settings.html";
        plotly_plotter::write_html(file_path, figure);
        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with x axis") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("x", std::vector<int>{1, 1, 1, 2, 2, 2, 5, 5, 5});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

        const auto figure = violin(data)
                                .x("x")
                                .y("y")
                                .points("all")
                                .title("Test Title")
                                .create();

        const std::string file_path = "violin_build_with_x_axis.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with x-axis and group") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("group",
            std::vector<std::string>{
                "A", "A", "A", "A", "A", "A", "B", "B", "B"});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("x", std::vector<int>{1, 1, 1, 2, 2, 2, 1, 1, 1});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

        const auto figure = violin(data)
                                .x("x")
                                .y("y")
                                .group("group")
                                .points("all")
                                .change_color_by_group()
                                .title("Test Title")
                                .create();

        const std::string file_path = "violin_build_with_x_and_group.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with columns of subplots") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("group", std::vector<int>{1, 1, 1, 2, 2, 2, 5, 5, 5});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

        const auto figure = violin(data)
                                .y("y")
                                .subplot_column("group")
                                .title("Test Title")
                                .create();

        const std::string file_path = "violin_build_with_subplot_column.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with hover") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("group", std::vector<int>{1, 1, 1, 2, 2, 2, 5, 5, 5});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        data.emplace("additional1",
            std::vector<std::string>{
                "a", "b", "c", "d", "e", "f", "g", "h", "i"});
        data.emplace("additional2",
            std::vector<std::string>{
                "A", "B", "C", "D", "E", "F", "G", "H", "I"});

        const auto figure = violin(data)
                                .y("y")
                                .hover_data({"additional1", "additional2"})
                                .points("all")
                                .title("Test Title")
                                .create();

        const std::string file_path = "violin_build_with_hover.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("change the color sequence") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("group", std::vector<int>{1, 1, 1, 2, 2, 2, 5, 5, 5});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

        const auto figure = violin(data)
                                .y("y")
                                .group("group")
                                .color_sequence({"#E66B0A", "#0E65E5"})
                                .title("Test Title")
                                .create();

        const std::string file_path = "violin_change_color_sequence.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("use fixed color") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("group", std::vector<int>{1, 1, 1, 2, 2, 2, 5, 5, 5});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

        const auto figure = violin(data)
                                .y("y")
                                .group("group")
                                .fixed_color("#E66B0A")
                                .title("Test Title")
                                .create();

        const std::string file_path = "violin_use_fixed_color.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("use mapping of groups to colors") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("group", std::vector<int>{1, 1, 1, 2, 2, 2, 5, 5, 5});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

        const auto figure = violin(data)
                                .y("y")
                                .group("group")
                                .color_map({{"1", "#E66B0A"}, {"2", "#0E65E5"},
                                    {"5", "#E514CD"}})
                                .title("Test Title")
                                .create();

        const std::string file_path =
            "violin_use_mapping_of_groups_to_colors.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with mean lines without boxes") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 5, 10});

        const auto figure =
            violin(data).y("y").show_box(false).show_mean_line(true).create();

        const std::string file_path =
            "violin_build_with_mean_lines_without_boxes.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with mean lines and boxes") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 5, 10});

        const auto figure =
            violin(data).y("y").show_box(true).show_mean_line(true).create();

        const std::string file_path =
            "violin_build_with_mean_lines_and_boxes.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with log scale") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 5, 50});

        const auto figure =
            violin(data).y("y").show_box(true).log_y(true).create();

        const std::string file_path = "violin_build_with_log_scale.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with log scale but with negative values") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 2, 3, 5, 50, -1});

        const auto figure =
            violin(data).y("y").show_box(true).log_y(true).create();

        const std::string file_path =
            "violin_build_with_log_scale_but_with_negative_values.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
