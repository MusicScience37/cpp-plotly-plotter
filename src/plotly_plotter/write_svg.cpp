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
 * \brief Implementation of write_svg function.
 */
#include "plotly_plotter/write_svg.h"

#include <filesystem>
#include <stdexcept>

#include "plotly_plotter/io/pdftocairo_converter.h"
#include "plotly_plotter/write_pdf.h"

namespace plotly_plotter {

namespace details {

void write_svg_impl(const char* file_path, const char* html_title,
    const json_document& data, std::size_t width, std::size_t height) {
    const std::string pdf_file_path = std::string(file_path) + ".pdf";
    write_pdf_impl(pdf_file_path.c_str(), html_title, data, width, height);

    if (io::pdftocairo_converter::get_instance()
            .is_pdf_to_svg_conversion_supported()) {
        io::pdftocairo_converter::get_instance().convert_pdf_to_svg(
            pdf_file_path.c_str(), file_path);
    } else {
        std::filesystem::remove(pdf_file_path);
        throw std::runtime_error("No supported PDF to SVG converter found.");
    }

    if (!std::filesystem::exists(file_path)) {
        throw std::runtime_error("Failed to create SVG file.");
    }
    std::filesystem::remove(pdf_file_path);
}

}  // namespace details

bool is_svg_supported() {
    return is_pdf_supported() &&
        io::pdftocairo_converter::get_instance()
            .is_pdf_to_svg_conversion_supported();
}

}  // namespace plotly_plotter
