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
#include "plotly_plotter/traces/scatter.h"

#include <string>
#include <string_view>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("scatter") {
    plotly_plotter::figure figure;

    SECTION("data types") {
        SECTION("double to double") {
            auto scatter = figure.add_scatter();
            scatter.x(std::vector{1.25, 2.5, 3.75});  // NOLINT(*-magic-numbers)
            scatter.y(std::vector{4.5, 5.75, 7.0});   // NOLINT(*-magic-numbers)

            const std::string file_path = "scatter_double_to_double.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("int to double") {
            auto scatter = figure.add_scatter();
            scatter.x(std::vector{1, 2, 3});
            scatter.y(std::vector{4.5, 5.75, 7.0});  // NOLINT(*-magic-numbers)

            const std::string file_path = "scatter_int_to_double.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("string to double") {
            auto scatter = figure.add_scatter();
            scatter.x(std::vector<std::string_view>{"a", "b", "c"});
            scatter.y(std::vector{4.5, 5.75, 7.0});  // NOLINT(*-magic-numbers)

            const std::string file_path = "scatter_string_to_double.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("modes") {
        auto scatter = figure.add_scatter();
        scatter.name("lines");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.text(std::vector{"A", "B", "C"});
        scatter.mode("lines");

        scatter = figure.add_scatter();
        scatter.name("markers");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{5, 6, 7});  // NOLINT(*-magic-numbers)
        scatter.text(std::vector{"A", "B", "C"});
        scatter.mode("markers");

        scatter = figure.add_scatter();
        scatter.name("lines+markers");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{6, 7, 8});  // NOLINT(*-magic-numbers)
        scatter.text(std::vector{"A", "B", "C"});
        scatter.mode("lines+markers");

        scatter = figure.add_scatter();
        scatter.name("lines+markers+text");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{7, 8, 9});  // NOLINT(*-magic-numbers)
        scatter.text(std::vector{"A", "B", "C"});
        scatter.mode("lines+markers+text");

        figure.title("Scatter Modes");

        const std::string file_path = "scatter_modes.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("hover templates") {
        auto scatter = figure.add_scatter();
        scatter.name("hover template");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.text(std::vector{"A", "B", "C<br>new line"});
        scatter.hover_template("x: %{x}<br>y: %{y:.2f}<br>text: %{text}");

        figure.title("Scatter Hover Templates");

        const std::string file_path = "scatter_hover_templates.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("set symmetric error bars") {
        auto scatter = figure.add_scatter();
        scatter.name("hover template");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.error_x().type("data");
        scatter.error_x().symmetric(true);
        scatter.error_x().visible(true);
        scatter.error_x().array(
            std::vector{0.25, 0.5, 0.75});  // NOLINT(*-magic-numbers)
        scatter.error_y().type("data");
        scatter.error_y().symmetric(true);
        scatter.error_y().visible(true);
        scatter.error_y().array(
            std::vector{0.5, 1.0, 1.5});  // NOLINT(*-magic-numbers)

        figure.title("Scatter with Symmetric Error Bars");

        const std::string file_path = "scatter_set_symmetric_error_bars.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("set asymmetric error bars") {
        auto scatter = figure.add_scatter();
        scatter.name("hover template");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.error_x().type("data");
        scatter.error_x().symmetric(false);
        scatter.error_x().visible(true);
        scatter.error_x().array(
            std::vector{0.125, 0.25, 0.375});  // NOLINT(*-magic-numbers)
        scatter.error_x().array_minus(
            std::vector{0.25, 0.5, 0.75});  // NOLINT(*-magic-numbers)
        scatter.error_y().type("data");
        scatter.error_y().symmetric(false);
        scatter.error_y().visible(true);
        scatter.error_y().array(
            std::vector{0.375, 0.75, 1.125});  // NOLINT(*-magic-numbers)
        scatter.error_y().array_minus(
            std::vector{0.5, 1.0, 1.5});  // NOLINT(*-magic-numbers)

        figure.title("Scatter with Asymmetric Error Bars");

        const std::string file_path = "scatter_set_asymmetric_error_bars.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("set error bars in log scale") {
        auto scatter = figure.add_scatter();
        scatter.name("hover template");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.error_x().type("data");
        scatter.error_x().symmetric(true);
        scatter.error_x().visible(true);
        scatter.error_x().array(
            std::vector{0.25, 0.5, 0.75});  // NOLINT(*-magic-numbers)
        scatter.error_y().type("data");
        scatter.error_y().symmetric(true);
        scatter.error_y().visible(true);
        scatter.error_y().array(
            std::vector{0.5, 1.0, 1.5});  // NOLINT(*-magic-numbers)

        figure.layout().xaxis().type("log");
        figure.layout().yaxis().type("log");

        figure.title("Scatter with Error Bars in Log Scale");

        const std::string file_path =
            "scatter_set_error_bars_in_log_scale.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("multiple scatters in subplots") {
        constexpr std::string_view color1 = "#3e3ae2";
        constexpr std::string_view color2 = "#53c842";

        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{5, 6, 7});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{6, 7, 8});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);
        scatter.show_legend(false);
        scatter.xaxis("x2");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{7, 8, 9});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.show_legend(false);
        scatter.xaxis("x2");

        figure.layout().grid().rows(1);
        figure.layout().grid().columns(2);

        figure.layout().xaxis(1).title().text("x1");
        figure.layout().xaxis(2).title().text("x2");

        figure.layout().yaxis().title().text("y");

        figure.layout().title().text("Scatters in Subplots");

        const std::string file_path = "scatter_in_subplots.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("set colors") {
        auto scatter = figure.add_scatter();
        scatter.name("hover template");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.error_x().type("data");
        scatter.error_x().symmetric(true);
        scatter.error_x().visible(true);
        scatter.error_x().array(
            std::vector{0.25, 0.5, 0.75});  // NOLINT(*-magic-numbers)
        scatter.error_y().type("data");
        scatter.error_y().symmetric(true);
        scatter.error_y().visible(true);
        scatter.error_y().array(
            std::vector{0.5, 1.0, 1.5});  // NOLINT(*-magic-numbers)
        scatter.color("#E66B0A");

        figure.title("Scatter with Setting of Colors");

        const std::string file_path = "scatter_set_colors.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("set dash") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.line().dash("solid");
        scatter.name("solid");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{5, 6, 7});  // NOLINT(*-magic-numbers)
        scatter.line().dash("dot");
        scatter.name("dot");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{6, 7, 8});  // NOLINT(*-magic-numbers)
        scatter.line().dash("dash");
        scatter.name("dash");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{7, 8, 9});  // NOLINT(*-magic-numbers)
        scatter.line().dash("longdash");
        scatter.name("longdash");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{8, 9, 10});  // NOLINT(*-magic-numbers)
        scatter.line().dash("dashdot");
        scatter.name("dashdot");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{9, 10, 11});  // NOLINT(*-magic-numbers)
        scatter.line().dash("longdashdot");
        scatter.name("longdashdot");

        figure.title("Scatter with Setting of Dash");

        const std::string file_path = "scatter_set_dash.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("colorize markers by data") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        scatter.y(std::vector{4, 5, 6});
        // NOLINTNEXTLINE(*-magic-numbers)
        scatter.marker().color(std::vector{7, 8, 9});
        scatter.marker().color_axis("coloraxis");
        // scatter.marker().show_scale(true);
        scatter.marker().size(30.0);  // NOLINT(*-magic-numbers)
        scatter.mode("markers");

        figure.layout().color_axis().show_scale(true);
        figure.layout().color_axis().c_min(6.0);   // NOLINT(*-magic-numbers)
        figure.layout().color_axis().c_max(10.0);  // NOLINT(*-magic-numbers)
        figure.layout().color_axis().color_bar().title().text("color axis");

        figure.title("Scatter with Colorize Markers by Data");

        const std::string file_path = "scatter_colorize_markers_by_data.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("change sizes of markers by data") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        // NOLINTNEXTLINE(*-magic-numbers)
        scatter.y(std::vector{4, 5, 6});
        // NOLINTNEXTLINE(*-magic-numbers)
        scatter.marker().size(std::vector{10, 30, 50});
        scatter.mode("markers");

        figure.title("Scatter with Change Sizes of Markers by Data");

        const std::string file_path =
            "scatter_change_sizes_of_markers_by_data.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
