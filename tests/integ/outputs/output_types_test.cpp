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
 * \brief Test of output types.
 */
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/scatter.h"
#include "plotly_plotter/traces/violin.h"
#include "plotly_plotter/write_html.h"
#include "plotly_plotter/write_pdf.h"
#include "plotly_plotter/write_png.h"
#include "plotly_plotter/write_svg.h"

TEST_CASE("output types") {
    plotly_plotter::figure figure;

    SECTION("scatter") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.mode("lines");
        scatter.name("scatter1");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{5, 6, 7});  // NOLINT(*-magic-numbers)
        scatter.mode("markers+lines");
        scatter.name("scatter2");

        figure.title("Scatter Plot");
        figure.layout().xaxis().title().text("x-axis");
        figure.layout().yaxis().title().text("y-axis");

        const std::string file_name = "output_types_scatter";
        SECTION("HTML") {
            CHECK_NOTHROW(
                plotly_plotter::write_html(file_name + ".html", figure));
        }
        SECTION("PDF") {
            if (plotly_plotter::is_pdf_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_pdf(file_name + ".pdf", figure));
            }
        }
        SECTION("PNG") {
            if (plotly_plotter::is_png_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_png(file_name + ".png", figure));
            }
        }
        SECTION("SVG") {
            if (plotly_plotter::is_svg_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_svg(file_name + ".svg", figure));
            }
        }
    }

    SECTION("violin") {
        auto violin = figure.add_violin();
        violin.x(std::vector{"A", "A", "A", "A", "B", "B", "B", "B", "B", "B"});
        // NOLINTNEXTLINE(*-magic-numbers)
        violin.y(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        violin.mean_line().visible(true);
        violin.box().visible(true);
        violin.name("Group 1");

        violin = figure.add_violin();
        violin.x(std::vector{"A", "A", "A", "A", "A", "A", "A", "B", "B", "B"});
        // NOLINTNEXTLINE(*-magic-numbers)
        violin.y(std::vector{2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
        violin.mean_line().visible(true);
        violin.box().visible(true);
        violin.name("Group 2");

        figure.layout().violin_mode("group");

        figure.title("Violin Plot");
        figure.layout().xaxis().title().text("x-axis");
        figure.layout().yaxis().title().text("y-axis");

        const std::string file_name = "output_types_violin";
        SECTION("HTML") {
            CHECK_NOTHROW(
                plotly_plotter::write_html(file_name + ".html", figure));
        }
        SECTION("PDF") {
            if (plotly_plotter::is_pdf_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_pdf(file_name + ".pdf", figure));
            }
        }
        SECTION("PNG") {
            if (plotly_plotter::is_png_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_png(file_name + ".png", figure));
            }
        }
        SECTION("SVG") {
            if (plotly_plotter::is_svg_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_svg(file_name + ".svg", figure));
            }
        }
    }

    SECTION("TeX") {
        auto scatter = figure.add_scatter();
        scatter.name("lines");
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

        figure.layout().title().text(R"($\text{Title with TeX: } \alpha$)");
        figure.layout().xaxis().title().text(
            R"($\text{x-axis title with TeX: } \beta^2$)");
        figure.layout().yaxis().title().text(
            R"($\text{y-axis title with TeX: } \gamma_3$)");

        const std::string file_name = "output_types_tex";
        SECTION("HTML") {
            CHECK_NOTHROW(
                plotly_plotter::write_html(file_name + ".html", figure));
        }
        SECTION("PDF") {
            if (plotly_plotter::is_pdf_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_pdf(file_name + ".pdf", figure));
            }
        }
        SECTION("PNG") {
            if (plotly_plotter::is_png_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_png(file_name + ".png", figure));
            }
        }
        SECTION("SVG") {
            if (plotly_plotter::is_svg_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_svg(file_name + ".svg", figure));
            }
        }
    }
}

TEST_CASE("output types (unstable)", "[!mayfail]") {
    plotly_plotter::figure figure;

    SECTION("WebGL") {
        constexpr std::size_t num_points = 1000;
        std::vector<double> x_vec;
        std::vector<double> y_vec;
        x_vec.reserve(num_points);
        y_vec.reserve(num_points);
        for (std::size_t i = 0; i < num_points; ++i) {
            const double x =
                static_cast<double>(i) / static_cast<double>(num_points - 1);
            const double y = x * x;
            x_vec.push_back(x);
            y_vec.push_back(y);
        }

        auto scatter = figure.add_scatter_gl();
        scatter.x(x_vec);
        scatter.y(y_vec);
        scatter.mode("lines");
        scatter.name("$y=x^2$");

        figure.title("Scatter Plot with Many Points Using WebGL");
        figure.layout().xaxis().title().text("$x$");
        figure.layout().yaxis().title().text("$y$");

        const std::string file_name = "output_types_web_gl";
        SECTION("HTML") {
            CHECK_NOTHROW(
                plotly_plotter::write_html(file_name + ".html", figure));
        }
        SECTION("PDF") {
            if (plotly_plotter::is_pdf_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_pdf(file_name + ".pdf", figure));
            }
        }
        SECTION("PNG") {
            if (plotly_plotter::is_png_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_png(file_name + ".png", figure));
            }
        }
        SECTION("SVG") {
            if (plotly_plotter::is_svg_supported()) {
                CHECK_NOTHROW(
                    plotly_plotter::write_svg(file_name + ".svg", figure));
            }
        }
    }
}
