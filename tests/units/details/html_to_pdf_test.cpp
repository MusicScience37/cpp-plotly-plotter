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
 * \brief Test of html_to_pdf function.
 */
#include "plotly_plotter/details/html_to_pdf.h"

#include <filesystem>

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("plotly_plotter::details::html_to_pdf") {
    // Figure for test.
    plotly_plotter::figure figure;
    auto scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

    // Create HTML file.
    const std::string html_file_path = "html_to_pdf_test.html";
    plotly_plotter::write_html(html_file_path, figure);

    SECTION("convert an HTML to a PDF") {
        const std::string pdf_file_path = "html_to_pdf_test.pdf";
        constexpr std::size_t width = 800;
        constexpr std::size_t height = 600;

#if defined(linux)
        CHECK_NOTHROW(plotly_plotter::details::html_to_pdf(
            html_file_path.c_str(), pdf_file_path.c_str(), width, height));
        CHECK(std::filesystem::exists(pdf_file_path));
#else
        CHECK_THROWS(plotly_plotter::details::html_to_pdf(
            html_file_path.c_str(), pdf_file_path.c_str(), width, height));
#endif
    }
}
