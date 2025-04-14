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
 * \brief Test of scatter plots.
 */
#include "plotly_plotter/figure_builders/scatter.h"

#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("scatter") {
    using plotly_plotter::data_table;
    using plotly_plotter::write_html;
    using plotly_plotter::figure_builders::scatter;

    SECTION("simple scatter plot") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6});

        const auto figure =
            scatter(data).x("x").y("y").title("Simple Scatter").create();
        const std::string file_path = "scatter_simple_scatter_plot.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("scatter with group") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3, 1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6, 7, 8, 9});
        data.emplace(
            "group", std::vector<std::string>{"A", "A", "A", "B", "B", "B"});

        const auto figure = scatter(data)
                                .x("x")
                                .y("y")
                                .group("group")
                                .title("Scatter with Group")
                                .create();
        const std::string file_path = "scatter_with_group.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("scatter with hover data") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6});
        data.emplace("hover", std::vector<std::string>{"A", "B", "C"});

        const auto figure = scatter(data)
                                .x("x")
                                .y("y")
                                .hover_data({"hover"})
                                .title("Scatter with Hover Data")
                                .create();
        const std::string file_path = "scatter_with_hover_data.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("log scale in x") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("x", std::vector<int>{1, 10, 100, 10, 100, 1000});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6, 7, 8, 9});
        data.emplace(
            "group", std::vector<std::string>{"A", "A", "A", "B", "B", "B"});

        const auto figure = scatter(data)
                                .x("x")
                                .y("y")
                                .subplot_row("group")
                                .log_x(true)
                                .title("Log Scale in X")
                                .create();
        const std::string file_path = "scatter_log_scale_x.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("log scale in y") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("x", std::vector<int>{1, 2, 3, 2, 3, 4});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{1, 10, 100, 10, 100, 1000});
        data.emplace(
            "group", std::vector<std::string>{"A", "A", "A", "B", "B", "B"});

        const auto figure = scatter(data)
                                .x("x")
                                .y("y")
                                .subplot_column("group")
                                .log_y(true)
                                .title("Log Scale in Y")
                                .create();
        const std::string file_path = "scatter_log_scale_y.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("log scale in x and y") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("x", std::vector<int>{1, 10, 100, 10, 100, 1000});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{2, 20, 200, 20, 200, 2000});
        data.emplace(
            "group", std::vector<std::string>{"A", "A", "A", "B", "B", "B"});

        const auto figure = scatter(data)
                                .x("x")
                                .y("y")
                                .subplot_row("group")
                                .log_x(true)
                                .log_y(true)
                                .title("Log Scale in X and Y")
                                .create();
        const std::string file_path = "scatter_log_scale_x_y.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("colorize markers") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("y", std::vector<int>{4, 5, 6});
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("color", std::vector<int>{7, 8, 9});

        auto figure = scatter(data)
                          .x("x")
                          .y("y")
                          .marker_color("color")
                          .title("Colorize Markers")
                          .create();

        // NOLINTNEXTLINE(*-magic-numbers)
        figure.layout().color_axis().c_min(6.0);
        // NOLINTNEXTLINE(*-magic-numbers)
        figure.layout().color_axis().c_max(9.0);

        figure.add_scatter_template().marker().size(20);

        const std::string file_path = "scatter_colorize_markers.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
