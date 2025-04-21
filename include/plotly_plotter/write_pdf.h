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
 * \brief Definition of write_pdf function.
 */
#pragma once

#include <cstddef>
#include <string>

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"

namespace plotly_plotter {

//! Default width of PDF files.
constexpr std::size_t default_pdf_width = 800;

//! Default height of PDF files.
constexpr std::size_t default_pdf_height = 600;

namespace details {

/*!
 * \brief Write a figure to a PDF file.
 *
 * \param[in] file_path File path.
 * \param[in] html_title Title of the HTML file.
 * \param[in] data Data.
 * \param[in] width Width of the PDF file.
 * \param[in] height Height of the PDF file.
 */
PLOTLY_PLOTTER_EXPORT void write_pdf_impl(const char* file_path,
    const char* html_title, const json_document& data, std::size_t width,
    std::size_t height);

}  // namespace details

/*!
 * \brief Check if PDF is supported in the current environment.
 *
 * \return True if PDF is supported.
 *
 * \note When this functions returns false, \ref plotly_plotter::write_pdf
 * function always fails with an exception.
 */
PLOTLY_PLOTTER_EXPORT bool is_pdf_supported();

/*!
 * \brief Write a figure to a PDF file.
 *
 * \param[in] file_path File path.
 * \param[in] fig Figure.
 * \param[in] width Width of the PDF file.
 * \param[in] height Height of the PDF file.
 *
 * \warning WebGL can cause errors sometimes.
 * \note Support of PDF output can be checked using \ref
 * plotly_plotter::is_pdf_supported function.
 */
inline void write_pdf(const std::string& file_path, const figure& fig,
    std::size_t width = default_pdf_width,
    std::size_t height = default_pdf_height) {
    details::write_pdf_impl(file_path.c_str(), fig.html_title().c_str(),
        fig.document(), width, height);
}

}  // namespace plotly_plotter
