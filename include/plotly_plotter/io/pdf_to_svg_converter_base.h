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
 * \brief Definition of pdf_to_svg_converter_base class.
 */
#pragma once

#include <cstddef>

#include "plotly_plotter/details/plotly_plotter_export.h"

namespace plotly_plotter::io {

/*!
 * \brief Base class for PDF to SVG converter.
 */
class PLOTLY_PLOTTER_EXPORT pdf_to_svg_converter_base {
public:
    /*!
     * \brief Get whether PDF to SVG conversion is supported in the
     * environment.
     *
     * \retval true PDF to SVG conversion is supported.
     * \retval false PDF to SVG conversion is not supported.
     */
    [[nodiscard]] virtual bool is_pdf_to_svg_conversion_supported() = 0;

    /*!
     * \brief Convert a PDF file to a SVG file.
     *
     * \param[in] pdf_file_path Path to the PDF file.
     * \param[in] svg_file_path Path to the SVG file.
     */
    virtual void convert_pdf_to_svg(
        const char* pdf_file_path, const char* svg_file_path) = 0;

    /*!
     * \brief Constructor.
     */
    pdf_to_svg_converter_base() = default;

    /*!
     * \brief Destructor.
     */
    virtual ~pdf_to_svg_converter_base();

    pdf_to_svg_converter_base(const pdf_to_svg_converter_base&) = delete;
    pdf_to_svg_converter_base(pdf_to_svg_converter_base&&) = delete;
    pdf_to_svg_converter_base& operator=(
        const pdf_to_svg_converter_base&) = delete;
    pdf_to_svg_converter_base& operator=(pdf_to_svg_converter_base&&) = delete;
};

}  // namespace plotly_plotter::io
