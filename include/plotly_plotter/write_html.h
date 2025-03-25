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
 * \brief Definition of write_html function.
 */
#pragma once

#include <string>

#include "plotly_plotter/details/write_html_impl.h"
#include "plotly_plotter/figure.h"

namespace plotly_plotter {

/*!
 * \brief Write a figure to an HTML file.
 *
 * \param[in] file_path File path.
 * \param[in] fig Figure.
 */
inline void write_html(const std::string& file_path, const figure& fig) {
    details::write_html_impl(file_path.c_str(), fig.html_title().c_str(),
        fig.document(), details::html_template_type::html,
        // Width and height are not used for HTML output, so arbitrary values
        // can be used.
        0, 0);
}

}  // namespace plotly_plotter
