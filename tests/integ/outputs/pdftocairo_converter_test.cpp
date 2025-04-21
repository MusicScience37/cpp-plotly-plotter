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
 * \brief Test of pdftocairo_converter class.
 */
#include "plotly_plotter/io/pdftocairo_converter.h"

#include <filesystem>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/details/config.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/figure_builders/line.h"
#include "plotly_plotter/figure_builders/scatter.h"
#include "plotly_plotter/write_pdf.h"

TEST_CASE("plotly_plotter::io::pdftocairo_converter") {
    // Create a figure for test.
    plotly_plotter::data_table data;
    data.emplace("x", std::vector{1, 2, 3});
    data.emplace("y", std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
    const auto figure = plotly_plotter::figure_builders::line(data)
                            .x("x")
                            .y("y")
                            .title("Test Figure")
                            .create();

    auto& converter = plotly_plotter::io::pdftocairo_converter::get_instance();

    SECTION("create a SVG file") {
        const std::string pdf_file_path = "pdftocairo_converter_svg_test.pdf";
        const std::string svg_file_path = "pdftocairo_converter_svg_test.svg";

#if PLOTLY_PLOTTER_USE_UNIX_SUBPROCESS
        CHECK(plotly_plotter::is_pdf_supported());
        CHECK(converter.is_pdf_to_svg_conversion_supported());
#endif

        if (plotly_plotter::is_pdf_supported() &&
            converter.is_pdf_to_svg_conversion_supported()) {
            CHECK_NOTHROW(plotly_plotter::write_pdf(pdf_file_path, figure));
            CHECK_NOTHROW(converter.convert_pdf_to_svg(
                pdf_file_path.c_str(), svg_file_path.c_str()));

            CHECK(std::filesystem::exists(svg_file_path));
        }
    }
}
