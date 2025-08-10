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
 * \brief Definition of calculate_histogram_bin_width function.
 */
#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

#include "plotly_plotter/details/plotly_plotter_export.h"

namespace plotly_plotter::utils {

/*!
 * \brief Calculate the width of histogram bins using the Freedman-Diaconis
 * rule.
 *
 * \tparam Container Type of the container of values.
 * \param[in] values Values.
 * \return Bin width.
 */
[[nodiscard]] PLOTLY_PLOTTER_EXPORT double
calculate_histogram_bin_width_freedman_diaconis(
    const std::vector<double>& values);

/*!
 * \brief Enumeration of methods to calculate bin widths of histograms.
 */
enum class histogram_bin_width_method : std::uint8_t {
    //! Freedman-Diaconis rule.
    freedman_diaconis,
};

/*!
 * \brief Calculate the width of histogram bins.
 *
 * \tparam Container Type of the container of values.
 * \param[in] values Values.
 * \param[in] method Method for calculation.
 * \return Bin width.
 */
template <typename Container>
[[nodiscard]] double calculate_histogram_bin_width(const Container& values,
    histogram_bin_width_method method =
        histogram_bin_width_method::freedman_diaconis) {
    std::vector<double> values_for_calculation;
    values_for_calculation.reserve(values.size());
    for (const auto& value : values) {
        values_for_calculation.push_back(static_cast<double>(value));
    }

    switch (method) {
    case histogram_bin_width_method::freedman_diaconis:
        return calculate_histogram_bin_width_freedman_diaconis(
            values_for_calculation);
    }
    throw std::invalid_argument("Unknown histogram bin width method");
}

}  // namespace plotly_plotter::utils
