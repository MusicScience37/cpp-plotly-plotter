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
 * \brief Test of bar trace.
 */
#include <string>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("bar") {
    plotly_plotter::figure figure;

    SECTION("simple bar trace") {
        auto bar = figure.add_bar();
        bar.x(std::vector{"A", "B", "C"});
        bar.y(std::vector{1, 2, 3});  // NOLINT(*-magic-numbers)

        const std::string file_path = "bar_simple.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("change color") {
        auto bar = figure.add_bar();
        bar.x(std::vector{"A", "B", "C"});
        bar.y(std::vector{1, 2, 3});  // NOLINT(*-magic-numbers)

        bar.marker().color("green");

        const std::string file_path = "bar_change_color.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("multiple bar plots") {
        auto bar = figure.add_bar();
        bar.x(std::vector{"A", "B", "C"});
        bar.y(std::vector{1, 2, 3});  // NOLINT(*-magic-numbers)

        bar = figure.add_bar();
        bar.x(std::vector{"A", "B", "C"});
        bar.y(std::vector{2, 3, 4});  // NOLINT(*-magic-numbers)

        SECTION("group") {
            figure.layout().bar_mode("group");

            const std::string file_path = "bar_multiple_group.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("stack") {
            figure.layout().bar_mode("stack");

            const std::string file_path = "bar_multiple_stack.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("overlay") {
            figure.layout().bar_mode("overlay");
            figure.add_bar_template().opacity(0.5);  // NOLINT(*-magic-numbers)

            const std::string file_path = "bar_multiple_overlay.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("set widths") {
        auto bar = figure.add_bar();
        bar.x(std::vector{"A", "B", "C"});
        bar.y(std::vector{1, 2, 3});  // NOLINT(*-magic-numbers)

        bar.width(std::vector{0.9, 0.7, 0.5});  // NOLINT(*-magic-numbers)

        const std::string file_path = "bar_set_widths.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("set width to a fixed value") {
        auto bar = figure.add_bar();
        bar.x(std::vector{"A", "B", "C"});
        bar.y(std::vector{1, 2, 3});  // NOLINT(*-magic-numbers)

        figure.add_bar_template().width(0.5);  // NOLINT(*-magic-numbers)

        const std::string file_path = "bar_set_width.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("log scale") {
        auto bar = figure.add_bar();
        bar.x(std::vector{1.5, 3.0, 6.0, 12.0});     // NOLINT(*-magic-numbers)
        bar.width(std::vector{1.0, 2.0, 4.0, 8.0});  // NOLINT(*-magic-numbers)
        bar.y(std::vector{1, 2, 3, 4});              // NOLINT(*-magic-numbers)

        figure.layout().xaxis().type("log");

        const std::string file_path = "bar_log_scale.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
