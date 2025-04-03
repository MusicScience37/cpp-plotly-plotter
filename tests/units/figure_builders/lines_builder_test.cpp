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
 * \brief Test of lines_builder class.
 */
#include "plotly_plotter/figure_builders/lines_builder.h"

#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("plotly_plotter::figure_builders::lines_builder") {
    using plotly_plotter::data_table;
    using plotly_plotter::figure_builders::lines_builder;

    SECTION("build with minimal settings") {
        data_table data;
        data.emplace("y", std::vector<int>{1, 2, 3});

        const auto figure = lines_builder(data).y("y").build();

        const std::string file_path =
            "lines_builder_build_with_minimal_settings.html";
        plotly_plotter::write_html(file_path, figure);
        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("build with full settings") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3});
        data.emplace("y", std::vector<int>{4, 5, 6});

        const auto figure =
            lines_builder(data).x("x").y("y").title("Test Title").build();

        const std::string file_path =
            "lines_builder_build_with_full_settings.html";
        plotly_plotter::write_html(file_path, figure);
        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
