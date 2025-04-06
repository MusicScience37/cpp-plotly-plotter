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
 * \brief Test of data types.
 */
#include <Eigen/Core>
#include <string>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure_builders/line.h"
#include "plotly_plotter/figure_builders/scatter.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("data types") {
    using plotly_plotter::data_table;
    using plotly_plotter::write_html;
    using plotly_plotter::figure_builders::line;

    SECTION("vector<int>") {
        data_table data;
        data.emplace("x", std::vector{1, 2, 3});
        data.emplace("y", std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

        const auto figure =
            line(data).x("x").y("y").title("Line with vector<int>").create();

        const std::string file_path = "data_types_vector_int.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("vector<float>") {
        data_table data;
        data.emplace("x", std::vector{1, 2, 3});
        data.emplace(
            "y", std::vector{4.5F, 5.75F, 7.0F});  // NOLINT(*-magic-numbers)

        const auto figure =
            line(data).x("x").y("y").title("Line with vector<float>").create();

        const std::string file_path = "data_types_vector_float.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("vector<double>") {
        data_table data;
        data.emplace("x", std::vector{1, 2, 3});
        data.emplace(
            "y", std::vector{4.5, 5.75, 7.0});  // NOLINT(*-magic-numbers)

        const auto figure =
            line(data).x("x").y("y").title("Line with vector<double>").create();

        const std::string file_path = "data_types_vector_double.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("vector<string>") {
        data_table data;
        data.emplace("x", std::vector<std::string>{"a", "b", "c"});
        data.emplace(
            "y", std::vector{4.5, 5.75, 7.0});  // NOLINT(*-magic-numbers)

        const auto figure =
            line(data).x("x").y("y").title("Line with vector<string>").create();

        const std::string file_path = "data_types_vector_string.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("Eigen::VectorXd") {
        data_table data;
        data.emplace("x", std::vector{1, 2, 3});
        data.emplace(
            "y", Eigen::VectorXd{{4.5, 5.75, 7.0}});  // NOLINT(*-magic-numbers)

        const auto figure = line(data)
                                .x("x")
                                .y("y")
                                .title("Line with Eigen::VectorXd")
                                .create();

        const std::string file_path = "data_types_eigen_vector_xd.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("Eigen::VectorXi") {
        data_table data;
        data.emplace("x", std::vector{1, 2, 3});
        data.emplace(
            "y", Eigen::VectorXi{{4, 5, 6}});  // NOLINT(*-magic-numbers)

        const auto figure = line(data)
                                .x("x")
                                .y("y")
                                .title("Line with Eigen::VectorXi")
                                .create();

        const std::string file_path = "data_types_eigen_vector_xi.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
