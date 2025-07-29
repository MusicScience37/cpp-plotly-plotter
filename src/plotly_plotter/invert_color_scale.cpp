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
 * \brief Implementation of invert_color_scale function.
 */
#include "plotly_plotter/invert_color_scale.h"

namespace plotly_plotter {

std::vector<std::pair<double, std::string>> invert_color_scale(
    const std::vector<std::pair<double, std::string>>& color_scale) {
    std::vector<std::pair<double, std::string>> inverted;
    inverted.reserve(color_scale.size());
    for (auto it = color_scale.rbegin(); it != color_scale.rend(); ++it) {
        inverted.emplace_back(1.0 - it->first, it->second);
    }
    return inverted;
}

}  // namespace plotly_plotter
