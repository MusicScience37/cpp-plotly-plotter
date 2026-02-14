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
 * \brief Get the color scale autumn.
 *
 * \return Color scale.
 *
 * A color map of yellow, orange, red and brown.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
autumn();

/*!
 * \brief Get the color scale autumn_wide.
 *
 * \return Color scale.
 *
 * A color map of white, yellow, orange, red and brown.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
autumn_wide();

/*!
 * \brief Get the color scale ocean.
 *
 * \return Color scale.
 *
 * A color maps of blues.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
ocean();

/*!
 * \brief Get the color scale ocean_wide.
 *
 * \return Color scale.
 *
 * A color maps of blues with wider range of lightness.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
ocean_wide();

/*!
 * \brief Get the color scale forest.
 *
 * \return Color scale.
 *
 * A color map of greens.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
forest();

/*!
 * \brief Get the color scale forest_wide.
 *
 * \return Color scale.
 *
 * A color map of greens with wider range of lightness.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
forest_wide();

/*!
 * \brief Get the color scale red.
 *
 * \return Color scale.
 *
 * A color map of reds.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
red();

/*!
 * \brief Get the color scale red_wide.
 *
 * \return Color scale.
 *
 * A color map of reds with wider range of lightness.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
red_wide();

/*!
 * \brief Get the color scale purple_green_yellow.
 *
 * \return Color scale.
 *
 * A color map of purple, green and yellow.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
purple_green_yellow();

/*!
 * \brief Get the color scale tea.
 *
 * \return Color scale.
 *
 * A color map of red and green.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
tea();

/*!
 * \brief Get the color scale blue_brown_white.
 *
 * \return Color scale.
 *
 * A color map of blue, white, and brown.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_brown_white();

/*!
 * \brief Get the color scale blue_brown_white_wide.
 *
 * \return Color scale.
 *
 * A color map of blue, white, and brown with wider range of lightness.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_brown_white_wide();

/*!
 * \brief Get the color scale blue_brown_light.
 *
 * \return Color scale.
 *
 * A color map of blue, green, and brown.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_brown_light();

/*!
 * \brief Get the color scale blue_brown_light_wide.
 *
 * \return Color scale.
 *
 * A color map of blue, green, and brown with wider range of lightness.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_brown_light_wide();

/*!
 * \brief Get the color scale blue_red_white.
 *
 * \return Color scale.
 *
 * A color map of blue, white, and red.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_red_white();

/*!
 * \brief Get the color scale blue_red_white_wide.
 *
 * \return Color scale.
 *
 * A color map of blue, white, and red with wider range of lightness.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_red_white_wide();

/*!
 * \brief Get the color scale blue_red_light.
 *
 * \return Color scale.
 *
 * A color map of blue, yellow, and red.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_red_light();

/*!
 * \brief Get the color scale blue_red_light_wide.
 *
 * \return Color scale.
 *
 * A color map of blue, yellow, and red with wider range of lightness.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_red_light_wide();

/*!
 * \brief Get the color scale blue_orange_dark.
 *
 * \return Color scale.
 *
 * A color map of blue, dark purple, and orange.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_orange_dark();

/*!
 * \brief Get the color scale blue_orange_dark_wide.
 *
 * \return Color scale.
 *
 * A color map of blue, dark purple, and orange with wider range of lightness.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_orange_dark_wide();

/*!
 * \brief Get the color scale blue_red_dark.
 *
 * \return Color scale.
 *
 * A color map of blue, dark purple, and red.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_red_dark();

/*!
 * \brief Get the color scale blue_red_dark_wide.
 *
 * \return Color scale.
 *
 * A color map of blue, dark purple, and red with wider range of lightness.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
blue_red_dark_wide();

/*!
 * \brief Get the color scale rainbow.
 *
 * \return Color scale.
 *
 * A color scale of blue, green and red.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
rainbow();

/*!
 * \brief Get the color scale equal_hue.
 *
 * \return Color scale.
 *
 * A cyclic color map whose color changes only in hue.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT std::vector<std::pair<double, std::string>>
equal_hue();

}  // namespace plotly_plotter::color_scales
