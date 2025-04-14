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
 * \brief Test of box plots.
 */
#include "plotly_plotter/traces/box.h"

#include <string>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("box") {
    plotly_plotter::figure figure;

    SECTION("simplest box plot") {
        auto box = figure.add_box();
        // NOLINTNEXTLINE(*-magic-numbers)
        box.y(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

        const std::string file_path = "box_simplest.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("set x, y, text") {
        auto box = figure.add_box();
        box.x(std::vector{"A", "A", "A", "A", "A", "B", "B", "B", "B", "B"});
        // NOLINTNEXTLINE(*-magic-numbers)
        box.y(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        box.text(std::vector{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"});
        box.hover_template("x: %{x}<br>y: %{y}<br>text: %{text}");
        box.box_points("all");

        const std::string file_path = "box_set_x_y_text.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("show mean and stddev") {
        const auto y = std::vector{1, 2, 3, 5, 8, 13};

        auto box = figure.add_box();
        box.y(y);
        box.box_mean(false);
        box.name("false");

        box = figure.add_box();
        box.y(y);
        box.box_mean(true);
        box.name("true");

        box = figure.add_box();
        box.y(y);
        box.box_mean("sd");
        box.name("sd");

        const std::string file_path = "box_show_mean_and_stddev.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("show points") {
        const auto y = std::vector{1, 2, 3, 5, 50};

        auto box = figure.add_box();
        box.y(y);
        box.box_points("all");
        box.name("all");

        box = figure.add_box();
        box.y(y);
        box.box_points("outliers");
        box.name("outliers");

        box = figure.add_box();
        box.y(y);
        box.box_points("suspectedoutliers");
        box.name("suspectedoutliers");

        box = figure.add_box();
        box.y(y);
        box.box_points("false");
        box.name("false");

        const std::string file_path = "box_show_points.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("group box plots") {
        auto box = figure.add_box();
        box.x(std::vector{"A", "A", "A", "A", "B", "B", "B", "B", "B", "B"});
        // NOLINTNEXTLINE(*-magic-numbers)
        box.y(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        box.name("Group 1");

        box = figure.add_box();
        box.x(std::vector{"A", "A", "A", "A", "A", "A", "A", "B", "B", "B"});
        // NOLINTNEXTLINE(*-magic-numbers)
        box.y(std::vector{2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
        box.name("Group 2");

        figure.layout().box_mode("group");

        const std::string file_path = "box_group_box_plots.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("multiple boxes in subplots") {
        constexpr std::string_view color1 = "#3e3ae2";
        constexpr std::string_view color2 = "#53c842";

        auto box = figure.add_box();
        // NOLINTNEXTLINE(*-magic-numbers)
        box.y(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        box.box_mean("sd");
        box.box_points("all");
        box.name("Box 1");
        box.legend_group("Box 1");
        box.color(color1);

        box = figure.add_box();
        // NOLINTNEXTLINE(*-magic-numbers)
        box.y(std::vector{2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
        box.box_mean("sd");
        box.box_points("all");
        box.name("Box 2");
        box.legend_group("Box 2");
        box.color(color2);

        box = figure.add_box();
        // NOLINTNEXTLINE(*-magic-numbers)
        box.y(std::vector{3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
        box.box_mean("sd");
        box.box_points("all");
        box.name("Box 1");
        box.legend_group("Box 1");
        box.color(color1);
        box.xaxis("x2");
        box.show_legend(false);

        box = figure.add_box();
        // NOLINTNEXTLINE(*-magic-numbers)
        box.y(std::vector{4, 5, 6, 7, 8, 9, 10, 11, 12, 13});
        box.box_mean("sd");
        box.box_points("all");
        box.name("Box 2");
        box.legend_group("Box 2");
        box.color(color2);
        box.xaxis("x2");
        box.show_legend(false);

        figure.layout().grid().rows(1);
        figure.layout().grid().columns(2);

        figure.layout().xaxis(1).title().text("x1");
        figure.layout().xaxis(2).title().text("x2");

        figure.layout().yaxis().title().text("y");

        figure.layout().title().text("Boxes in Subplots");

        const std::string file_path = "box_in_subplots.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("use a template") {
        auto box = figure.add_box();
        // NOLINTNEXTLINE(*-magic-numbers)
        box.y(std::vector{1, 2, 3, 5, 8, 13});

        figure.add_box_template().box_mean("sd");

        figure.title("Box with a Template");

        const std::string file_path = "box_with_a_template.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
