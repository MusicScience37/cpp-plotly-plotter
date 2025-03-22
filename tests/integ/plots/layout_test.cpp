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
 * \brief Test of layouts.
 */
#include "plotly_plotter/layout.h"

#include <string>
#include <string_view>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/traces/scatter.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("layout") {
    plotly_plotter::figure figure;

    SECTION("add titles") {
        auto scatter = figure.add_scatter();
        scatter.name("lines");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

        figure.layout().title().text("Title");
        figure.layout().xaxis().title().text("x-axis title");
        figure.layout().yaxis().title().text("y-axis title");

        const std::string file_path = "layout_add_titles.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("add titles with escaped characters") {
        auto scatter = figure.add_scatter();
        scatter.name("lines");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

        figure.title("Title with escaped characters: & < > \" '");
        figure.layout().xaxis().title().text(
            "x-axis title with escaped characters: & < > \" '");
        figure.layout().yaxis().title().text(
            "y-axis title with escaped characters: & < > \" '");

        const std::string file_path =
            "layout_add_titles_with_escaped_characters.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("add titles with TeX") {
        auto scatter = figure.add_scatter();
        scatter.name("lines");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

        figure.layout().title().text(R"($\text{Title with TeX: } \alpha$)");
        figure.layout().xaxis().title().text(
            R"($\text{x-axis title with TeX: } \beta^2$)");
        figure.layout().yaxis().title().text(
            R"($\text{y-axis title with TeX: } \gamma_3$)");

        const std::string file_path = "layout_add_titles_with_tex.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("add titles with non-ASCII characters") {
        auto scatter = figure.add_scatter();
        scatter.name("lines");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

        figure.title("タイトル");
        figure.layout().xaxis().title().text("x軸");
        figure.layout().yaxis().title().text("y軸");

        const std::string file_path = "layout_add_titles_with_non_ascii.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
