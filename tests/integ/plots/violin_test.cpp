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
 * \brief Test of violin plots.
 */
#include "plotly_plotter/traces/violin.h"

#include <string>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("violin") {
    plotly_plotter::figure figure;

    SECTION("simplest violin plot") {
        auto violin = figure.add_violin();
        // NOLINTNEXTLINE(*-magic-numbers)
        violin.y(std::vector{1, 1, 2, 2, 3, 3, 4, 5, 50});

        const std::string file_path = "violin_simplest.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("set x, y, text") {
        auto violin = figure.add_violin();
        violin.x(std::vector{"A", "A", "A", "A", "A", "B", "B", "B", "B", "B"});
        // NOLINTNEXTLINE(*-magic-numbers)
        violin.y(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        violin.text(
            std::vector{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"});
        violin.hover_template("x: %{x}<br>y: %{y}<br>text: %{text}");
        violin.points("all");

        const std::string file_path = "violin_set_x_y_text.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("show mean line") {
        const auto y = std::vector{1, 2, 3, 5, 8, 13};
        auto violin = figure.add_violin();
        violin.y(y);
        violin.mean_line().visible(true);

        const std::string file_path = "violin_show_mean_line.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("show box") {
        const auto y = std::vector{1, 2, 3, 5, 8, 13};
        auto violin = figure.add_violin();
        violin.y(y);
        violin.box().visible(true);

        const std::string file_path = "violin_show_box.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("show mean line and box") {
        const auto y = std::vector{1, 2, 3, 5, 8, 13};
        auto violin = figure.add_violin();
        violin.y(y);
        violin.mean_line().visible(true);
        violin.box().visible(true);

        const std::string file_path = "violin_show_mean_line_and_box.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("show points") {
        const auto y = std::vector{1, 2, 3, 5, 50};

        auto violin = figure.add_violin();
        violin.y(y);
        violin.box().visible(true);
        violin.points("all");
        violin.name("all");

        violin = figure.add_violin();
        violin.y(y);
        violin.box().visible(true);
        violin.points("outliers");
        violin.name("outliers");

        violin = figure.add_violin();
        violin.y(y);
        violin.box().visible(true);
        violin.points("suspectedoutliers");
        violin.name("suspectedoutliers");

        violin = figure.add_violin();
        violin.y(y);
        violin.box().visible(true);
        violin.points("false");
        violin.name("false");

        const std::string file_path = "violin_show_points.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("group violin plots") {
        auto violin = figure.add_violin();
        violin.x(std::vector{"A", "A", "A", "A", "B", "B", "B", "B", "B", "B"});
        // NOLINTNEXTLINE(*-magic-numbers)
        violin.y(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        violin.name("Group 1");

        violin = figure.add_violin();
        violin.x(std::vector{"A", "A", "A", "A", "A", "A", "A", "B", "B", "B"});
        // NOLINTNEXTLINE(*-magic-numbers)
        violin.y(std::vector{2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
        violin.name("Group 2");

        figure.layout().violin_mode("group");

        const std::string file_path = "violin_group_violin_plots.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
