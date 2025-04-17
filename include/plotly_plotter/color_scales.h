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
 * \brief Declaration of functions of color scales.
 *
 * This file is generated from a template
 * scripts/templates/color_scales.h.jinja
 * using a script scripts/color_scale_util.py.
 */
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "plotly_plotter/details/plotly_plotter_export.h"

namespace plotly_plotter::color_scales {

/*!
 * \brief Get the color scale gray.
 *
 * \return Color scale.
 *
 * A color scale of gray scale from black to white.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
gray();

/*!
 * \brief Get the color scale inverted_gray.
 *
 * \return Color scale.
 *
 * A color scale of gray scale from white to black.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
inverted_gray();

/*!
 * \brief Get the color scale cool_warm_simple.
 *
 * \return Color scale.
 *
 * A simple color scale of blue, white and red.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
cool_warm_simple();

/*!
 * \brief Get the color scale cool_warm_darker.
 *
 * \return Color scale.
 *
 * A color scale of blue, white and red including more dark colors.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
cool_warm_darker();

/*!
 * \brief Get the color scale cool_warm_extended.
 *
 * \return Color scale.
 *
 * A color scale of blue, white and red including more dark colors and light
 * colors.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
cool_warm_extended();

/*!
 * \brief Get the color scale cool_warm_extended_relaxed.
 *
 * \return Color scale.
 *
 * A color scale of blue, white and red including more dark colors and light
 * colors, with a more relaxed transition at zero.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
cool_warm_extended_relaxed();

/*!
 * \brief Get the color scale cool_extended.
 *
 * \return Color scale.
 *
 * A color scale of blue and white including dark and light colors.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
cool_extended();

/*!
 * \brief Get the color scale warm_extended.
 *
 * \return Color scale.
 *
 * A color scale of white and red including dark and light colors.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
warm_extended();

/*!
 * \brief Get the color scale blown.
 *
 * \return Color scale.
 *
 * A color scale of white, orange and blown.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blown();

/*!
 * \brief Get the color scale autumn.
 *
 * \return Color scale.
 *
 * A color scale of yellow, orange, red and brown.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
autumn();

/*!
 * \brief Get the color scale autumn_full.
 *
 * \return Color scale.
 *
 * A color scale of white, yellow, orange, red, brown and black.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
autumn_full();

/*!
 * \brief Get the color scale green.
 *
 * \return Color scale.
 *
 * A color scale of green.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
green();

/*!
 * \brief Get the color scale green_full.
 *
 * \return Color scale.
 *
 * A color scale of white, green and black.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
green_full();

/*!
 * \brief Get the color scale blue.
 *
 * \return Color scale.
 *
 * A color scale of blue.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue();

/*!
 * \brief Get the color scale blue_full.
 *
 * \return Color scale.
 *
 * A color scale of white, blue and black.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_full();

/*!
 * \brief Get the color scale purple_green_yellow.
 *
 * \return Color scale.
 *
 * A color scale of purple, green and yellow.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
purple_green_yellow();

/*!
 * \brief Get the color scale blue_purple_red.
 *
 * \return Color scale.
 *
 * A color scale of blue, purple and red.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_purple_red();

/*!
 * \brief Get the color scale blue_green_red.
 *
 * \return Color scale.
 *
 * A color scale of blue, green and red.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_green_red();

/*!
 * \brief Get the color scale whole_hue.
 *
 * \return Color scale.
 *
 * A color scale of the whole hue.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
whole_hue();

}  // namespace plotly_plotter::color_scales
