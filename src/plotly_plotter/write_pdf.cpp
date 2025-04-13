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
 * \brief Implementation of write_pdf function.
 */
#include "plotly_plotter/write_pdf.h"

#include <filesystem>
#include <stdexcept>

#include "plotly_plotter/details/write_html_impl.h"
#include "plotly_plotter/io/chrome_converter.h"
#include "plotly_plotter/io/playwright_converter.h"

namespace plotly_plotter {

namespace details {

void write_pdf_impl(const char* file_path, const char* html_title,
    const json_document& data, std::size_t width, std::size_t height) {
    const std::string html_file_path = std::string(file_path) + ".html";
    write_html_impl(html_file_path.c_str(), html_title, data,
        html_template_type::pdf, width, height);

    if (io::playwright_converter::get_instance()
            .is_html_to_pdf_conversion_supported()) {
        io::playwright_converter::get_instance().convert_html_to_pdf(
            html_file_path.c_str(), file_path, width, height);
    } else if (io::chrome_converter::get_instance()
                   .is_html_to_pdf_conversion_supported()) {
        io::chrome_converter::get_instance().convert_html_to_pdf(
            html_file_path.c_str(), file_path, width, height);
    } else {
        std::filesystem::remove(html_file_path);
        throw std::runtime_error("No supported HTML to PDF converter found.");
    }

    if (!std::filesystem::exists(file_path)) {
        throw std::runtime_error("Failed to create PDF file.");
    }
    std::filesystem::remove(html_file_path);
}

}  // namespace details

bool is_pdf_supported() {
    return io::playwright_converter::get_instance()
               .is_html_to_pdf_conversion_supported() ||
        io::chrome_converter::get_instance()
            .is_html_to_pdf_conversion_supported();
}

}  // namespace plotly_plotter
