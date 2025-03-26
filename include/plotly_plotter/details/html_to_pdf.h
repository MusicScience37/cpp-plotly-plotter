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
 * \brief Declaration of html_to_pdf function.
 */
#pragma once

#include <cstddef>

#include "plotly_plotter/details/plotly_plotter_export.h"

namespace plotly_plotter::details {

/*!
 * \brief Check whether PDF is supported in the environment.
 *
 * \return Whether PDF is supported.
 */
PLOTLY_PLOTTER_EXPORT [[nodiscard]] bool is_pdf_supported();

/*!
 * \brief Convert an HTML file to a PDF file.
 *
 * \param[in] html_file_path Path to the HTML file.
 * \param[in] pdf_file_path Path to the PDF file.
 * \param[in] width Width of the PDF file.
 * \param[in] height Height of the PDF file.
 * \param[in] capture_logs Whether to capture logs. When true, logs are captured
 * and not shown unless an error occurs.
 */
PLOTLY_PLOTTER_EXPORT void html_to_pdf(const char* html_file_path,
    const char* pdf_file_path, std::size_t width, std::size_t height,
    bool capture_logs = true);

}  // namespace plotly_plotter::details
