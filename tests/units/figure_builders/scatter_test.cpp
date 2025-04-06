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
 * \brief Test of scatter class.
 */
#include "plotly_plotter/figure_builders/scatter.h"

#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("plotly_plotter::figure_builders::scatter") {
    using plotly_plotter::data_table;
    using plotly_plotter::figure_builders::scatter;

    SECTION("build with minimal settings") {
        data_table data;
        data.emplace("y", std::vector<int>{1, 2, 3});

        const auto figure = scatter(data).y("y").create();

        const std::string file_path =
            "scatter_build_with_minimal_settings.html";
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
            scatter(data).x("x").y("y").title("Test Title").create();

        const std::string file_path = "scatter_build_without_grouping.html";
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

        const auto figure = scatter(data)
                                .x("x")
                                .y("y")
                                .group("group")
                                .mode("lines+markers")
                                .use_web_gl(false)
                                .hover_data({"additional1", "additional2"})
                                .title("Test Title")
                                .create();

        const std::string file_path = "scatter_build_with_full_settings.html";
        plotly_plotter::write_html(file_path, figure);
        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("use WebGL") {
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

        const auto figure = scatter(data)
                                .x("x")
                                .y("y")
                                .group("group")
                                .mode("lines+markers")
                                .use_web_gl(true)
                                .hover_data({"additional1", "additional2"})
                                .title("Test Title")
                                .create();

        const std::string file_path = "scatter_use_web_gl.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("try to build without y") {
        data_table data;
        data.emplace("x", std::vector<int>{1, 2, 3});

        REQUIRE_THROWS_AS(scatter(data).create(), std::runtime_error);
        REQUIRE_THROWS_AS(
            scatter(data).group("x").create(), std::runtime_error);
    }
}
