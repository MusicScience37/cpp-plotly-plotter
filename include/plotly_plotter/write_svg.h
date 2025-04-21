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
 * \brief Definition of write_svg function.
 */
#pragma once

#include <cstddef>
#include <string>

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"

namespace plotly_plotter {

//! Default width of SVG files.
constexpr std::size_t default_svg_width = 800;

//! Default height of SVG files.
constexpr std::size_t default_svg_height = 600;

namespace details {

/*!
 * \brief Write a figure to a SVG file.
 *
 * \param[in] file_path File path.
 * \param[in] html_title Title of the HTML file.
 * \param[in] data Data.
 * \param[in] width Width of the SVG file.
 * \param[in] height Height of the SVG file.
 */
PLOTLY_PLOTTER_EXPORT void write_svg_impl(const char* file_path,
    const char* html_title, const json_document& data, std::size_t width,
    std::size_t height);

}  // namespace details

/*!
 * \brief Check if SVG is supported in the current environment.
 *
 * \return True if SVG is supported.
 *
 * \note When this functions returns false, \ref plotly_plotter::write_svg
 * function always fails with an exception.
 */
PLOTLY_PLOTTER_EXPORT bool is_svg_supported();

/*!
 * \brief Write a figure to a SVG file.
 *
 * \param[in] file_path File path.
 * \param[in] fig Figure.
 * \param[in] width Width of the SVG file.
 * \param[in] height Height of the SVG file.
 *
 * \warning WebGL can cause errors sometimes.
 * \note Support of SVG output can be checked using \ref
 * plotly_plotter::is_svg_supported function.
 */
inline void write_svg(const std::string& file_path, const figure& fig,
    std::size_t width = default_svg_width,
    std::size_t height = default_svg_height) {
    details::write_svg_impl(file_path.c_str(), fig.html_title().c_str(),
        fig.document(), width, height);
}

}  // namespace plotly_plotter
