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
 * \brief Definition of escape_for_html function.
 */
#pragma once

#include <string>

namespace plotly_plotter::details {

/*!
 * \brief Escape a string for HTML.
 *
 * \param[in] input Input string.
 * \return Result string.
 */
[[nodiscard]] inline std::string escape_for_html(const std::string& input) {
    const auto input_view = std::string_view(input.data(), input.size());
    std::string output;
    // Heuristics to suppress resize.
    const std::size_t reserved_size = input_view.size() * 2;
    output.reserve(reserved_size);
    for (const char c : input_view) {
        switch (c) {
        case '&':
            output.append("&amp;");
            break;
        case '<':
            output.append("&lt;");
            break;
        case '>':
            output.append("&gt;");
            break;
        case '\"':
            output.append("&quot;");
            break;
        case '\'':
            output.append("&#x27;");
            break;
        default:
            output.push_back(c);
        }
    }
    return output;
}

}  // namespace plotly_plotter::details
