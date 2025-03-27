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
 * \brief Definition of write_html_impl function.
 */
#pragma once

#include <cstddef>
#include <cstdint>

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/json_document.h"

namespace plotly_plotter::details {

/*!
 * \brief Enumeration of HTML template types.
 */
enum class html_template_type : std::uint8_t {
    //! Template for HTML output.
    html = 1,

    //! Template for PDF output.
    pdf = 2,

    //! Template for PNG output.
    png = 3
};

/*!
 * \brief Write a figure to an HTML file.
 *
 * \param[in] file_path File path.
 * \param[in] html_title Title of the HTML file.
 * \param[in] data Data.
 * \param[in] template_type Template type.
 * \param[in] width Width of the plot. (Used for PDF output.)
 * \param[in] height Height of the plot. (Used for PDF output.)
 */
PLOTLY_PLOTTER_EXPORT void write_html_impl(const char* file_path,
    const char* html_title, const json_document& data,
    html_template_type template_type, std::size_t width, std::size_t height);

}  // namespace plotly_plotter::details
