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
 * \brief Test of chrome_converter class.
 */
#include "plotly_plotter/io/chrome_converter.h"

#include <filesystem>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/details/write_html_impl.h"
#include "plotly_plotter/figure_builders/line.h"

TEST_CASE("plotly_plotter::io::chrome_converter") {
    // Create a figure for test.
    plotly_plotter::data_table data;
    data.emplace("x", std::vector{1, 2, 3});
    data.emplace("y", std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
    const auto figure = plotly_plotter::figure_builders::line(data)
                            .x("x")
                            .y("y")
                            .title("Test Figure")
                            .create();

    auto& converter = plotly_plotter::io::chrome_converter::get_instance();

    SECTION("create a PDF file") {
        const std::string html_file_path = "chrome_converter_pdf_test.html";
        const std::string pdf_file_path = "chrome_converter_pdf_test.pdf";
        constexpr std::size_t width = 1600;
        constexpr std::size_t height = 900;

        plotly_plotter::details::write_html_impl(html_file_path.c_str(),
            figure.html_title().c_str(), figure.document(),
            plotly_plotter::details::html_template_type::pdf, width, height);

#ifdef linux
        CHECK(converter.is_html_to_pdf_conversion_supported());
        CHECK_NOTHROW(converter.convert_html_to_pdf(
            html_file_path.c_str(), pdf_file_path.c_str(), width, height));

        CHECK(std::filesystem::exists(pdf_file_path));
#else
        CHECK_FALSE(converter.is_html_to_pdf_conversion_supported());
        CHECK_THROWS(converter.convert_html_to_pdf(
            html_file_path.c_str(), pdf_file_path.c_str(), width, height));
#endif
    }

    SECTION("create a PNG file") {
        const std::string html_file_path = "chrome_converter_png_test.html";
        const std::string png_file_path = "chrome_converter_png_test.png";
        constexpr std::size_t width = 1600;
        constexpr std::size_t height = 900;

        plotly_plotter::details::write_html_impl(html_file_path.c_str(),
            figure.html_title().c_str(), figure.document(),
            plotly_plotter::details::html_template_type::png, width, height);
#ifdef linux
        CHECK(converter.is_html_to_png_conversion_supported());
        CHECK_NOTHROW(converter.convert_html_to_png(
            html_file_path.c_str(), png_file_path.c_str(), width, height));

        CHECK(std::filesystem::exists(png_file_path));
#else
        CHECK_FALSE(converter.is_html_to_png_conversion_supported());
        CHECK_THROWS(converter.convert_html_to_png(
            html_file_path.c_str(), png_file_path.c_str(), width, height));
#endif
    }
}
