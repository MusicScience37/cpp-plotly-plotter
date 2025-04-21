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
 * \brief Definition of write_png function.
 */
#pragma once

#include <cstddef>
#include <string>

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"

namespace plotly_plotter {

//! Default width of PNG files.
constexpr std::size_t default_png_width = 800;

//! Default height of PNG files.
constexpr std::size_t default_png_height = 600;

namespace details {

/*!
 * \brief Write a figure to a PNG file.
 *
 * \param[in] file_path File path.
 * \param[in] html_title Title of the HTML file.
 * \param[in] data Data.
 * \param[in] width Width of the PNG file.
 * \param[in] height Height of the PNG file.
 */
PLOTLY_PLOTTER_EXPORT void write_png_impl(const char* file_path,
    const char* html_title, const json_document& data, std::size_t width,
    std::size_t height);

}  // namespace details

/*!
 * \brief Check if PNG is supported in the current environment.
 *
 * \return True if PNG is supported.
 *
 * \note When this functions returns false, \ref plotly_plotter::write_png
 * function always fails with an exception.
 */
PLOTLY_PLOTTER_EXPORT bool is_png_supported();

/*!
 * \brief Write a figure to a PNG file.
 *
 * \param[in] file_path File path.
 * \param[in] fig Figure.
 * \param[in] width Width of the PNG file.
 * \param[in] height Height of the PNG file.
 *
 * \warning WebGL can cause errors sometimes.
 * \note Support of PNG output can be checked using \ref
 * plotly_plotter::is_png_supported function.
 */
inline void write_png(const std::string& file_path, const figure& fig,
    std::size_t width = default_png_width,
    std::size_t height = default_png_height) {
    details::write_png_impl(file_path.c_str(), fig.html_title().c_str(),
        fig.document(), width, height);
}

}  // namespace plotly_plotter
