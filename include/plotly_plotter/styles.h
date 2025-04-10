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
 * \brief Declarations of functions of styles of figures.
 */
#pragma once

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/layout.h"

namespace plotly_plotter::styles {

/*!
 * \brief Set a simple style of a figure.
 *
 * \param[out] layout Layout of the figure.
 * \param[in] num_xaxes Number of x-axes.
 * \param[in] num_yaxes Number of y-axes.
 */
PLOTLY_PLOTTER_EXPORT void simple_style(plotly_plotter::layout layout,
    std::size_t num_xaxes = 1, std::size_t num_yaxes = 1);

}  // namespace plotly_plotter::styles
