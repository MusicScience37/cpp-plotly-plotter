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
 * \brief Definition of write_html function.
 */
#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

#include "plotly_plotter/details/escape_for_html.h"
#include "plotly_plotter/details/file_handle.h"
#include "plotly_plotter/details/templates/plotly_plot_template.h"
#include "plotly_plotter/figure.h"

namespace plotly_plotter {

namespace details {

/*!
 * \brief Check whether an input string starts with a prefix.
 *
 * \param[in] string Input string.
 * \param[in] prefix Prefix.
 * \retval true Input string starts with the prefix.
 * \retval false Input string does not start with the prefix.
 *
 * \note This function works like `std::string::starts_with` in C++20.
 */
inline bool starts_with(std::string_view string, std::string_view prefix) {
    return string.substr(0, prefix.size()) == prefix;
}

}  // namespace details

/*!
 * \brief Write a figure to an HTML file.
 *
 * \param[in] file_path File path.
 * \param[in] fig Figure.
 */
inline void write_html(const std::string& file_path, const figure& fig) {
    details::file_handle file(file_path, "w");

    std::string_view remaining_template =
        details::templates::plotly_plot_template;

    while (!remaining_template.empty()) {
        const std::size_t next_placeholder = remaining_template.find("{{");
        if (next_placeholder == std::string_view::npos) {
            file.write(remaining_template);
            break;
        }
        file.write(remaining_template.substr(0, next_placeholder));
        remaining_template = remaining_template.substr(next_placeholder);

        constexpr std::string_view title_placeholder = "{{ title }}";
        constexpr std::string_view escaped_data_placeholder =
            "{{ escaped_data }}";
        if (details::starts_with(remaining_template, title_placeholder)) {
            file.write(details::escape_for_html(fig.html_title()));
            remaining_template =
                remaining_template.substr(title_placeholder.size());
        } else if (details::starts_with(
                       remaining_template, escaped_data_placeholder)) {
            file.write(
                details::escape_for_html(fig.document().serialize_to_string()));
            remaining_template =
                remaining_template.substr(escaped_data_placeholder.size());
        } else {
            throw std::runtime_error("Invalid placeholder in the template.");
        }
    }
}

}  // namespace plotly_plotter
