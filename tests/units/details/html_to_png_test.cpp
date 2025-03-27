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
 * \brief Test of html_to_png function.
 */
#include "plotly_plotter/details/html_to_png.h"

#include <filesystem>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/details/write_html_impl.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/traces/scatter.h"

TEST_CASE("plotly_plotter::details::html_to_png") {
    // Figure for test.
    plotly_plotter::figure figure;
    auto scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

    // Create HTML file.
    const std::string html_file_path = "html_to_png_test.html";
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;
    plotly_plotter::details::write_html_impl(html_file_path.c_str(),
        figure.html_title().c_str(), figure.document(),
        plotly_plotter::details::html_template_type::pdf, width, height);

    SECTION("convert an HTML to a PDF") {
        const std::string png_file_path = "html_to_png_test.png";

#if defined(linux)
        // Development environment should have google-chrome installed.
        CHECK(plotly_plotter::details::is_png_supported());
        CHECK_NOTHROW(plotly_plotter::details::html_to_png(
            html_file_path.c_str(), png_file_path.c_str(), width, height));
        CHECK(std::filesystem::exists(png_file_path));
#else
        CHECK_FALSE(plotly_plotter::details::is_png_supported());
        CHECK_THROWS(plotly_plotter::details::html_to_png(
            html_file_path.c_str(), png_file_path.c_str(), width, height));
#endif
    }
}
