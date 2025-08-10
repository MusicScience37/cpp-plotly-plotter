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
 * \brief Test of histograms.
 */
#include "plotly_plotter/figure_builders/histogram.h"

#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("histogram") {
    using plotly_plotter::data_table;
    using plotly_plotter::write_html;
    using plotly_plotter::figure_builders::histogram;

    SECTION("simple histogram") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("values", std::vector<int>{1, 2, 3, 5, 10});

        const auto figure =
            histogram(data).x("values").title("Simple Histogram").create();

        const std::string file_path = "histogram_simple_histogram.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("histogram with a group") {
        data_table data;
        // NOLINTNEXTLINE(*-magic-numbers)
        data.emplace("values", std::vector<int>{0, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        data.emplace("group",
            std::vector<std::string>{
                "A", "A", "A", "A", "A", "A", "B", "B", "B", "B"});

        SECTION("in group") {
            const auto figure = histogram(data)
                                    .x("values")
                                    .group("group")
                                    .title("Test Title")
                                    .create();

            const std::string file_path = "histogram_with_group_in_group.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in columns of subplots") {
            const auto figure = histogram(data)
                                    .x("values")
                                    .subplot_column("group")
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "histogram_with_group_in_columns_of_subplots.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in rows of subplots") {
            const auto figure = histogram(data)
                                    .x("values")
                                    .subplot_row("group")
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "histogram_with_group_in_rows_of_subplots.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in animation frames") {
            const auto figure = histogram(data)
                                    .x("values")
                                    .animation_frame("group")
                                    .title("Test Title")
                                    .create();

            const std::string file_path =
                "histogram_with_group_in_animation_frames.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }
}
