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
 * \brief Implementation of write_html function.
 */
#include "plotly_plotter/details/write_html_impl.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>

#include <fmt/format.h>

#include "plotly_plotter/details/escape_for_html.h"
#include "plotly_plotter/details/file_handle.h"
#include "plotly_plotter/details/templates/plotly_plot.h"
#include "plotly_plotter/details/templates/plotly_plot_pdf.h"
#include "plotly_plotter/json_document.h"

namespace plotly_plotter::details {

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

[[nodiscard]] std::string_view get_template(html_template_type template_type) {
    switch (template_type) {
    case html_template_type::html:
        return details::templates::plotly_plot;
    case html_template_type::pdf:
        return details::templates::plotly_plot_pdf;
    default:
        throw std::runtime_error("Invalid template type.");
    }
}

void write_html_impl(const char* file_path, const char* html_title,
    const json_document& data, html_template_type template_type,
    std::size_t width, std::size_t height) {
    details::file_handle file(file_path, "w");

    std::string_view remaining_template = get_template(template_type);

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
        constexpr std::string_view width_placeholder = "{{ width }}";
        constexpr std::string_view height_placeholder = "{{ height }}";
        if (details::starts_with(remaining_template, title_placeholder)) {
            file.write(details::escape_for_html(html_title));
            remaining_template =
                remaining_template.substr(title_placeholder.size());
        } else if (details::starts_with(
                       remaining_template, escaped_data_placeholder)) {
            file.write(details::escape_for_html(data.serialize_to_string()));
            remaining_template =
                remaining_template.substr(escaped_data_placeholder.size());
        } else if (details::starts_with(
                       remaining_template, width_placeholder)) {
            file.write(fmt::to_string(width));
            remaining_template =
                remaining_template.substr(width_placeholder.size());
        } else if (details::starts_with(
                       remaining_template, height_placeholder)) {
            file.write(fmt::to_string(height));
            remaining_template =
                remaining_template.substr(height_placeholder.size());
        } else {
            throw std::runtime_error("Invalid placeholder in the template.");
        }
    }
}

}  // namespace plotly_plotter::details
