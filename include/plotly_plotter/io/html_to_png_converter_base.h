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
 * \brief Definition of html_to_png_converter_base class.
 */
#pragma once

#include <cstddef>

#include "plotly_plotter/details/plotly_plotter_export.h"

namespace plotly_plotter::io {

/*!
 * \brief Base class for HTML to PNG converter.
 */
class PLOTLY_PLOTTER_EXPORT html_to_png_converter_base {
public:
    /*!
     * \brief Get whether HTML to PNG conversion is supported in the
     * environment.
     *
     * \retval true HTML to PNG conversion is supported.
     * \retval false HTML to PNG conversion is not supported.
     */
    [[nodiscard]] virtual bool is_html_to_png_conversion_supported() = 0;

    /*!
     * \brief Convert an HTML file to a PNG file.
     *
     * \param[in] html_file_path Path to the HTML file.
     * \param[in] png_file_path Path to the PNG file.
     * \param[in] width Width of the PNG file.
     * \param[in] height Height of the PNG file.
     */
    virtual void convert_html_to_png(const char* html_file_path,
        const char* png_file_path, std::size_t width, std::size_t height) = 0;

    /*!
     * \brief Constructor.
     */
    html_to_png_converter_base() = default;

    /*!
     * \brief Destructor.
     */
    virtual ~html_to_png_converter_base();

    html_to_png_converter_base(const html_to_png_converter_base&) = delete;
    html_to_png_converter_base(html_to_png_converter_base&&) = delete;
    html_to_png_converter_base& operator=(
        const html_to_png_converter_base&) = delete;
    html_to_png_converter_base& operator=(
        html_to_png_converter_base&&) = delete;
};

}  // namespace plotly_plotter::io
