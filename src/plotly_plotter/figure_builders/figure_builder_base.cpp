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
 * \brief Implementation of figure_builder_base class.
 */
#include "plotly_plotter/figure_builders/figure_builder_base.h"

#include <cstddef>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"

namespace plotly_plotter::figure_builders {

figure figure_builder_base::create() const {
    if (group_.empty()) {
        return create_without_grouping();
    }
    return create_with_grouping();
}

figure_builder_base::figure_builder_base(const data_table& data)
    : data_(data) {}

void figure_builder_base::set_group(std::string value) {
    group_ = std::move(value);
}

void figure_builder_base::set_hover_data(std::vector<std::string> value) {
    hover_data_ = std::move(value);
}

void figure_builder_base::set_title(std::string value) {
    title_ = std::move(value);
}

const data_table& figure_builder_base::data() const noexcept { return data_; }

figure figure_builder_base::create_without_grouping() const {
    figure fig;

    const auto additional_hover_text = generate_additional_hover_text();
    add_trace_without_grouping(fig, additional_hover_text);

    configure_figure(fig);

    return fig;
}

figure figure_builder_base::create_with_grouping() const {
    figure fig;

    const auto additional_hover_text = generate_additional_hover_text();
    std::vector<std::string> additional_hover_text_filtered;
    additional_hover_text_filtered.reserve(additional_hover_text.size());

    const auto grouping = data_.at(group_)->generate_group();
    const auto& group_values = grouping.first;
    const auto& group_indices = grouping.second;

    std::vector<bool> group_mask(group_indices.size(), false);
    for (std::size_t group_index = 0; group_index < group_values.size();
        ++group_index) {
        for (std::size_t row_index = 0; row_index < group_indices.size();
            ++row_index) {
            group_mask[row_index] = (group_indices[row_index] == group_index);
        }

        additional_hover_text_filtered.clear();
        for (std::size_t row_index = 0; row_index < group_indices.size();
            ++row_index) {
            if (group_mask[row_index]) {
                additional_hover_text_filtered.push_back(
                    additional_hover_text[row_index]);
            }
        }

        const auto group_name =
            fmt::format("{}={}", group_, group_values[group_index]);
        const auto hover_prefix = fmt::format("{}<br>", group_name);
        add_trace_for_group(fig, group_mask, group_name, hover_prefix,
            additional_hover_text_filtered);
    }

    configure_figure(fig);

    return fig;
}

void figure_builder_base::configure_figure(figure& fig) const {
    configure_axes(fig);
    if (title_.empty()) {
        fig.layout().title().text(default_title());
    } else {
        fig.layout().title().text(title_);
    }
}

std::vector<std::string> figure_builder_base::generate_additional_hover_text()
    const {
    const std::size_t rows = data_.rows();
    std::vector<std::string> additional_hover_text(rows);
    for (const std::string& column_name : hover_data_) {
        const auto column = data_.at(column_name);
        const auto [group_values, group_indices] = column->generate_group();
        for (std::size_t row_index = 0; row_index < rows; ++row_index) {
            fmt::memory_buffer buffer;
            fmt::format_to(std::back_inserter(buffer), "<br>{}={}", column_name,
                group_values[group_indices[row_index]]);
            additional_hover_text[row_index].append(
                buffer.data(), buffer.size());
        }
    }
    return additional_hover_text;
}

}  // namespace plotly_plotter::figure_builders
