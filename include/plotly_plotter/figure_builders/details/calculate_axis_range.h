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
 * \brief Definition of calculate_axis_range function.
 */
#pragma once

#include <cmath>
#include <memory>
#include <string>
#include <utility>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/data_table.h"

namespace plotly_plotter::figure_builders::details {

/*!
 * \brief Calculate the range of an axis in linear scale.
 *
 * \param[in] data Data.
 * \param[in] column_name Column name.
 * \param[in] extended_factor Factor of extension from the range of data.
 * \return Minimum and maximum values of the axis.
 */
[[nodiscard]] inline std::pair<double, double> calculate_axis_range_in_linear(
    const data_table& data, const std::string& column_name,
    double extended_factor) {
    const auto [min, max] = data.at(column_name)->get_range();
    const double range = max - min;
    const double min_extended = min - extended_factor * range;
    const double max_extended = max + extended_factor * range;
    return {min_extended, max_extended};
}

/*!
 * \brief Calculate the range of an axis in log scale.
 *
 * \param[in] data Data.
 * \param[in] column_name Column name.
 * \param[in] extended_factor Factor of extension from the range of data.
 * \return Minimum and maximum values of the axis.
 */
[[nodiscard]] inline std::pair<double, double> calculate_axis_range_in_log(
    const data_table& data, const std::string& column_name,
    double extended_factor) {
    const auto [min, max] = data.at(column_name)->get_positive_range();
    const double min_log = std::log10(min);
    const double max_log = std::log10(max);
    const double range_log = max_log - min_log;
    const double min_log_extended = min_log - extended_factor * range_log;
    const double max_log_extended = max_log + extended_factor * range_log;
    return {min_log_extended, max_log_extended};
}

/*!
 * \brief Calculate the range of an axis.
 *
 * \param[in] data Data.
 * \param[in] column_name Column name.
 * \param[in] extended_factor Factor of extension from the range of data.
 * \param[in] log_scale Whether to use log scale.
 * \return Minimum and maximum values of the axis.
 */
[[nodiscard]] inline std::pair<double, double> calculate_axis_range(
    const data_table& data, const std::string& column_name,
    double extended_factor, bool log_scale) {
    if (log_scale) {
        return calculate_axis_range_in_log(data, column_name, extended_factor);
    }
    return calculate_axis_range_in_linear(data, column_name, extended_factor);
}

}  // namespace plotly_plotter::figure_builders::details
