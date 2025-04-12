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
 * \brief Declarations of internal common functions of figure builders.
 */
#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#include "plotly_plotter/figure.h"

namespace plotly_plotter::figure_builders::details {

/*!
 * \brief Configure common settings of axes.
 *
 * \param[out] fig Figure.
 * \param[in] num_subplot_rows Number of rows of subplots.
 * \param[in] num_subplot_columns Number of columns of subplots.
 * \param[in] x_title Title of x-axis.
 * \param[in] y_title Title of y-axis.
 */
void configure_axes_common(figure& fig, std::size_t num_subplot_rows,
    std::size_t num_subplot_columns, std::string_view x_title,
    std::string_view y_title);

/*!
 * \brief Add hover text to a trace.
 *
 * \tparam Trace Type of the trace.
 * \param[out] trace Trace.
 * \param[in] parent_mask Mask of the values in the parent layer.
 * \param[in] additional_hover_text Additional hover text.
 */
template <typename Trace>
void add_hover_text(Trace& trace, const std::vector<bool>& parent_mask,
    const std::vector<std::string>& additional_hover_text) {
    std::vector<std::string> additional_hover_text_filtered;
    additional_hover_text_filtered.reserve(additional_hover_text.size());
    for (std::size_t row_index = 0; row_index < parent_mask.size();
        ++row_index) {
        if (parent_mask[row_index]) {
            additional_hover_text_filtered.push_back(
                additional_hover_text[row_index]);
        }
    }
    trace.text(additional_hover_text_filtered);
}

}  // namespace plotly_plotter::figure_builders::details
