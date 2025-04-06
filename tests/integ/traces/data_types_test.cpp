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
#include <ctime>
#include <string>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/traces/scatter.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("data types") {
    plotly_plotter::figure figure;

    SECTION("vector<int>") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

        const std::string file_path = "data_types_vector_int.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("vector<float>") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4.5F, 5.75F, 7.0F});  // NOLINT(*-magic-numbers)

        const std::string file_path = "data_types_vector_float.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("vector<double>") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4.5, 5.75, 7.0});  // NOLINT(*-magic-numbers)

        const std::string file_path = "data_types_vector_double.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("vector<string>") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector<std::string>{"a", "b", "c"});
        scatter.y(std::vector{4.5, 5.75, 7.0});  // NOLINT(*-magic-numbers)

        const std::string file_path = "data_types_vector_string.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("vector<timespec>") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{
            // 2025-03-23 23:22:14.123456789 UTC
            std::timespec{1742772134, 123456789},  // NOLINT(*-magic-numbers)
            // 2025-03-23 23:22:15.234567890 UTC
            std::timespec{1742772135, 234567890},  // NOLINT(*-magic-numbers)
            // 2025-03-23 23:22:17.345678901 UTC
            std::timespec{1742772137, 345678901}  // NOLINT(*-magic-numbers)
        });
        scatter.y(std::vector{4.5, 5.75, 7.0});  // NOLINT(*-magic-numbers)

        const std::string file_path = "data_types_vector_timespec.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("Eigen::VectorXd") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(
            Eigen::VectorXd{{4.5, 5.75, 7.0}});  // NOLINT(*-magic-numbers)

        const std::string file_path = "data_types_eigen_vector_xd.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("Eigen::VectorXi") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(Eigen::VectorXi{{4, 5, 6}});  // NOLINT(*-magic-numbers)

        const std::string file_path = "data_types_eigen_vector_xi.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
