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
 * \brief Test of heatmaps.
 */
#include "plotly_plotter/traces/heatmap.h"

#include <Eigen/Core>
#include <string>
#include <string_view>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/eigen.h"  // IWYU pragma: keep
#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("heatmap") {
    plotly_plotter::figure figure;

    SECTION("simple heatmap") {
        auto heatmap = figure.add_heatmap();
        heatmap.z(
            // NOLINTNEXTLINE(*-magic-numbers)
            Eigen::MatrixXd{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
        heatmap.color_axis("coloraxis");
        heatmap.name("heatmap 1");

        figure.layout().color_axis().show_scale(true);

        const std::string file_path = "heatmap_simple_heatmap.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("heatmap with matrix with coordinates of centers") {
        auto heatmap = figure.add_heatmap();
        heatmap.z(
            // NOLINTNEXTLINE(*-magic-numbers)
            Eigen::MatrixXd{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
        heatmap.x(std::vector{1, 2, 3});
        heatmap.y(std::vector{2, 3, 4});
        heatmap.color_axis("coloraxis");

        figure.layout().color_axis().show_scale(true);
        figure.layout().color_axis().color_bar().title().text("color axis");
        figure.layout().color_axis().c_min(0.0);   // NOLINT(*-magic-numbers)
        figure.layout().color_axis().c_max(10.0);  // NOLINT(*-magic-numbers)

        figure.layout().xaxis().title().text("x");
        figure.layout().yaxis().title().text("y");

        figure.layout().title().text("Heatmap with Matrix");

        const std::string file_path = "heatmap_with_matrix_centers.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("heatmap with matrix with coordinates of edges") {
        auto heatmap = figure.add_heatmap();
        heatmap.z(
            // NOLINTNEXTLINE(*-magic-numbers)
            Eigen::MatrixXd{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
        heatmap.x(std::vector{1, 2, 3, 4});
        heatmap.y(std::vector{2, 3, 4, 5});  // NOLINT(*-magic-numbers)
        heatmap.color_axis("coloraxis");

        figure.layout().color_axis().show_scale(true);
        figure.layout().color_axis().color_bar().title().text("color axis");
        figure.layout().color_axis().c_min(0.0);   // NOLINT(*-magic-numbers)
        figure.layout().color_axis().c_max(10.0);  // NOLINT(*-magic-numbers)

        figure.layout().xaxis().title().text("x");
        figure.layout().yaxis().title().text("y");

        figure.layout().title().text("Heatmap with Matrix");

        const std::string file_path = "heatmap_with_matrix_edges.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("heatmap with vectors") {
        auto heatmap = figure.add_heatmap();
        heatmap.x(std::vector{1, 2, 3, 1, 2, 3, 1, 2, 3});
        heatmap.y(std::vector{1, 1, 1, 2, 2, 2, 3, 3, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        heatmap.z(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9});
        heatmap.color_axis("coloraxis");

        figure.layout().color_axis().show_scale(true);
        figure.layout().color_axis().color_bar().title().text("color axis");
        figure.layout().color_axis().c_min(0.0);   // NOLINT(*-magic-numbers)
        figure.layout().color_axis().c_max(10.0);  // NOLINT(*-magic-numbers)

        figure.layout().xaxis().title().text("x");
        figure.layout().yaxis().title().text("y");

        figure.layout().title().text("Heatmap with Vectors");

        const std::string file_path = "heatmap_with_vectors.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("heatmap with smoothing") {
        auto heatmap = figure.add_heatmap();
        heatmap.z(
            // NOLINTNEXTLINE(*-magic-numbers)
            Eigen::MatrixXd{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
        heatmap.x(std::vector{1, 2, 3});
        heatmap.y(std::vector{2, 3, 4});
        heatmap.color_axis("coloraxis");
        heatmap.z_smooth("best");

        figure.layout().color_axis().show_scale(true);
        figure.layout().color_axis().color_bar().title().text("color axis");
        figure.layout().color_axis().c_min(0.0);   // NOLINT(*-magic-numbers)
        figure.layout().color_axis().c_max(10.0);  // NOLINT(*-magic-numbers)

        figure.layout().xaxis().title().text("x");
        figure.layout().yaxis().title().text("y");

        figure.layout().title().text("Heatmap with Smoothing");

        const std::string file_path = "heatmap_with_smoothing.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("heatmap in square axes") {
        auto heatmap = figure.add_heatmap();
        heatmap.z(
            // NOLINTNEXTLINE(*-magic-numbers)
            Eigen::MatrixXd{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
        heatmap.x(std::vector{1, 2, 3});
        heatmap.y(std::vector{2, 3, 4});
        heatmap.color_axis("coloraxis");

        figure.layout().color_axis().show_scale(true);
        figure.layout().color_axis().color_bar().title().text("color axis");

        figure.layout().xaxis().title().text("x");
        figure.layout().yaxis().title().text("y");
        figure.square_axis();

        figure.title("Heatmap in Square Axes");

        const std::string file_path = "heatmap_in_square_axes.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
