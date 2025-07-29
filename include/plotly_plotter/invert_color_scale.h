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
 * \brief Declaration of invert_color_scale function.
 */
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "plotly_plotter/details/plotly_plotter_export.h"

namespace plotly_plotter {

/*!
 * \brief Invert the order of colors in a color scale.
 *
 * \param[in] color_scale Color scale to be inverted.
 * \return Inverted color scale.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
invert_color_scale(
    const std::vector<std::pair<double, std::string>>& color_scale);

}  // namespace plotly_plotter
