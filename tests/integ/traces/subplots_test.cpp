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
 * \brief Test of subplots.
 */
#include <string>
#include <string_view>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/scatter.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("subplots") {
    plotly_plotter::figure figure;

    constexpr std::string_view color1 = "#3e3ae2";
    constexpr std::string_view color2 = "#53c842";

    SECTION("subplots in columns") {
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

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{8, 9, 10});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);
        scatter.show_legend(false);
        scatter.xaxis("x3");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{9, 10, 11});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.show_legend(false);
        scatter.xaxis("x3");

        figure.layout().grid().rows(1);
        figure.layout().grid().columns(3);

        figure.layout().xaxis(1).title().text("x1");
        figure.layout().xaxis(2).title().text("x2");
        figure.layout().xaxis(3).title().text("x3");

        figure.layout().yaxis().title().text("y");

        figure.layout().title().text("Subplots in Columns");

        const std::string file_path = "subplots_in_columns.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("subplots in rows") {
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
        scatter.color(color1);
        scatter.show_legend(false);
        scatter.yaxis("y2");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{7, 8, 9});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.show_legend(false);
        scatter.yaxis("y2");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{8, 9, 10});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);
        scatter.show_legend(false);
        scatter.yaxis("y3");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{9, 10, 11});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.show_legend(false);
        scatter.yaxis("y3");

        figure.layout().grid().rows(3);
        figure.layout().grid().columns(1);

        figure.layout().xaxis().title().text("x");

        figure.layout().yaxis(1).title().text("y1");
        figure.layout().yaxis(2).title().text("y2");
        figure.layout().yaxis(3).title().text("y3");

        figure.layout().title().text("Subplots in Rows");

        const std::string file_path = "subplots_in_rows.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("subplots in table") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);
        scatter.xaxis("x");
        scatter.yaxis("y");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{5, 6, 7});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.xaxis("x");
        scatter.yaxis("y");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{6, 7, 8});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);
        scatter.show_legend(false);
        scatter.xaxis("x2");
        scatter.yaxis("y");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{7, 8, 9});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.show_legend(false);
        scatter.xaxis("x2");
        scatter.yaxis("y");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{8, 9, 10});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);
        scatter.show_legend(false);
        scatter.xaxis("x3");
        scatter.yaxis("y");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{9, 10, 11});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.show_legend(false);
        scatter.xaxis("x3");
        scatter.yaxis("y");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{10, 11, 12});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);
        scatter.show_legend(false);
        scatter.xaxis("x");
        scatter.yaxis("y2");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{11, 12, 13});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.show_legend(false);
        scatter.xaxis("x");
        scatter.yaxis("y2");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{12, 13, 14});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);
        scatter.show_legend(false);
        scatter.xaxis("x2");
        scatter.yaxis("y2");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{13, 14, 15});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.show_legend(false);
        scatter.xaxis("x2");
        scatter.yaxis("y2");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{14, 15, 16});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 1");
        scatter.legend_group("scatter 1");
        scatter.color(color1);
        scatter.show_legend(false);
        scatter.xaxis("x3");
        scatter.yaxis("y2");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{15, 16, 17});  // NOLINT(*-magic-numbers)
        scatter.name("scatter 2");
        scatter.legend_group("scatter 2");
        scatter.color(color2);
        scatter.show_legend(false);
        scatter.xaxis("x3");
        scatter.yaxis("y2");

        figure.layout().grid().rows(2);
        figure.layout().grid().columns(3);

        figure.layout().xaxis(1).title().text("x1");
        figure.layout().xaxis(2).title().text("x2");
        figure.layout().xaxis(3).title().text("x3");
        figure.layout().yaxis(1).title().text("y1");
        figure.layout().yaxis(2).title().text("y2");

        figure.layout().title().text("Subplots in Table");

        const std::string file_path = "subplots_in_table.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
