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
 * \brief Implementation of calculate_histogram_bin_width function.
 */
#include "plotly_plotter/utils/calculate_histogram_bin_width.h"

#include <cmath>
#include <stdexcept>

#include "plotly_plotter/utils/percentile_calculator.h"

namespace plotly_plotter::utils {

double calculate_histogram_bin_width_freedman_diaconis(
    const std::vector<double>& values) {
    if (values.empty()) {
        throw std::invalid_argument(
            "No values given to histogram bin calculation.");
    }

    percentile_calculator<double> percentiles(values);
    const auto interquartile_range =
        // NOLINTNEXTLINE(*-magic-numbers)
        static_cast<double>(
            percentiles.percentile(0.75) - percentiles.percentile(0.25));

    // NOLINTNEXTLINE(*-magic-numbers)
    return 2.0 * interquartile_range / std::cbrt(values.size());
}

}  // namespace plotly_plotter::utils
