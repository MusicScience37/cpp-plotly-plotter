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
 * \brief Definition of percentile_calculator class.
 */
#pragma once

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "plotly_plotter/details/has_iterator.h"

namespace plotly_plotter::figure_builders::details {

/*!
 * \brief Class to calculate percentiles.
 *
 * \tparam Value Type of values.
 */
template <typename Value>
class percentile_calculator {
public:
    static_assert(std::is_arithmetic_v<Value>,
        "Value type must be an arithmetic type (e.g., int, float, double).");

    /*!
     * \brief Constructor.
     *
     * \param[in] values Values to calculate percentiles.
     */
    template <typename Container,
        typename = std::enable_if_t<
            plotly_plotter::details::has_iterator_v<Container>>>
    explicit percentile_calculator(const Container& values)
        : sorted_values_(std::begin(values), std::end(values)) {
        if (sorted_values_.empty()) {
            throw std::runtime_error(
                "No values available for percentile calculation.");
        }
        std::sort(sorted_values_.begin(), sorted_values_.end());
    }

    /*!
     * \brief Calculate a percentile.
     *
     * \param[in] ratio Ratio to calculate a percentile of. (0.0 - 1.0)
     * \return Percentile value.
     */
    [[nodiscard]] Value percentile(double ratio) const {
        if (sorted_values_.empty()) {
            throw std::runtime_error(
                "No values available for percentile calculation.");
        }
        if (ratio < 0.0 || ratio > 1.0) {
            throw std::invalid_argument("Ratio must be between 0.0 and 1.0.");
        }

        const double index = ratio * (sorted_values_.size() - 1);
        const auto lower_index = static_cast<std::size_t>(index);
        if (std::abs(static_cast<double>(lower_index) - index) <
            std::numeric_limits<double>::epsilon()) {
            return sorted_values_[lower_index];
        }

        const std::size_t upper_index = lower_index + 1;
        assert(upper_index < sorted_values_.size());
        return sorted_values_[lower_index] +
            static_cast<Value>(
                (sorted_values_[upper_index] - sorted_values_[lower_index]) *
                (index - static_cast<double>(lower_index)));
    }

private:
    //! Sorted values.
    std::vector<Value> sorted_values_;
};

}  // namespace plotly_plotter::figure_builders::details
