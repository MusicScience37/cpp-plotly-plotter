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
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <fmt/base.h>
#include <fmt/format.h>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"

namespace plotly_plotter::figure_builders {

figure figure_builder_base::create() const {
    if (!data_.has_consistent_rows()) {
        throw std::runtime_error("Data table has inconsistent number of rows.");
    }

    figure fig;

    if (!subplot_row_.empty() || !subplot_column_.empty()) {
        fig.layout().grid().rows(1);
        fig.layout().grid().columns(1);
        constexpr double spacing = 0.1;
        fig.layout().grid().x_gap(spacing);
        fig.layout().grid().y_gap(spacing);
        fig.layout().grid().pattern("independent");
    }

    const std::vector<bool> parent_mask(data_.rows(), true);
    constexpr std::string_view hover_prefix;
    const auto additional_hover_text = generate_additional_hover_text();
    const auto [num_subplot_rows, num_subplot_columns] = handle_subplot_row(
        fig, parent_mask, hover_prefix, additional_hover_text);

    configure_figure(fig, num_subplot_rows, num_subplot_columns);
    fig.layout().legend().trace_group_gap(0.0);

    return fig;
}

figure_builder_base::figure_builder_base(const data_table& data)
    : data_(data) {}

void figure_builder_base::set_group(std::string value) {
    group_ = std::move(value);
}

void figure_builder_base::set_subplot_row(std::string value) {
    subplot_row_ = std::move(value);
}

void figure_builder_base::set_subplot_column(std::string value) {
    subplot_column_ = std::move(value);
}

void figure_builder_base::set_hover_data(std::vector<std::string> value) {
    hover_data_ = std::move(value);
}

void figure_builder_base::set_title(std::string value) {
    title_ = std::move(value);
}

const data_table& figure_builder_base::data() const noexcept { return data_; }

namespace {

//! Position of the annotation to place at the center.
constexpr double annotation_center = 0.5;

//! Position of the annotation to place at the end.
constexpr double annotation_end = 1.0;

//! Shift of the annotation to place at the end.
constexpr double annotation_shift = 30;

}  // namespace

std::pair<std::size_t, std::size_t> figure_builder_base::handle_subplot_row(
    figure& fig, const std::vector<bool>& parent_mask,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    if (subplot_row_.empty()) {
        const std::size_t first_subplot_index = 1;
        const std::size_t num_columns = handle_subplot_column(fig, parent_mask,
            first_subplot_index, hover_prefix, additional_hover_text);
        return {1, num_columns};
    }

    const auto grouping = data_.at(subplot_row_)->generate_group();
    const auto& group_values = grouping.first;
    const auto& group_indices = grouping.second;

    std::vector<bool> group_mask(group_indices.size(), false);
    std::size_t first_subplot_index_in_row = 1;
    std::size_t num_subplot_columns = 1;
    for (std::size_t group_index = 0; group_index < group_values.size();
        ++group_index) {
        for (std::size_t row_index = 0; row_index < group_indices.size();
            ++row_index) {
            group_mask[row_index] = parent_mask[row_index] &&
                (group_indices[row_index] == group_index);
        }

        const auto& group_value = group_values[group_index];
        const auto group_name = fmt::format("{}={}", subplot_row_, group_value);
        const auto group_hover_prefix =
            fmt::format("{}{}<br>", hover_prefix, group_name);
        num_subplot_columns =
            handle_subplot_column(fig, group_mask, first_subplot_index_in_row,
                group_hover_prefix, additional_hover_text);

        first_subplot_index_in_row += num_subplot_columns;

        const std::size_t annotation_subplot_index =
            first_subplot_index_in_row - 1;
        std::string x_ref;
        std::string y_ref;
        if (annotation_subplot_index == 1) {
            x_ref = "x domain";
            y_ref = "y domain";
        } else {
            x_ref = fmt::format("x{} domain", annotation_subplot_index);
            y_ref = fmt::format("y{} domain", annotation_subplot_index);
        }
        auto annotation = fig.layout().add_annotation();
        annotation.x_ref(x_ref);
        annotation.y_ref(y_ref);
        annotation.x(annotation_end);
        annotation.y(annotation_center);
        annotation.x_shift(annotation_shift);
        annotation.text_angle(90.0);  // NOLINT(*-magic-numbers)
        annotation.show_arrow(false);
        annotation.align("center");
        annotation.text(group_name);
    }

    fig.layout().grid().rows(group_values.size());

    return {group_values.size(), num_subplot_columns};
}

std::size_t figure_builder_base::handle_subplot_column(figure& fig,
    const std::vector<bool>& parent_mask, std::size_t first_subplot_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    if (subplot_column_.empty()) {
        handle_groups(fig, parent_mask, first_subplot_index, hover_prefix,
            additional_hover_text);
        return 1;
    }

    const auto grouping = data_.at(subplot_column_)->generate_group();
    const auto& group_values = grouping.first;
    const auto& group_indices = grouping.second;

    std::vector<bool> group_mask(group_indices.size(), false);
    for (std::size_t group_index = 0; group_index < group_values.size();
        ++group_index) {
        for (std::size_t row_index = 0; row_index < group_indices.size();
            ++row_index) {
            group_mask[row_index] = parent_mask[row_index] &&
                (group_indices[row_index] == group_index);
        }

        const auto& group_value = group_values[group_index];
        const auto group_name =
            fmt::format("{}={}", subplot_column_, group_value);
        const auto group_hover_prefix =
            fmt::format("{}{}<br>", hover_prefix, group_name);
        const std::size_t subplot_index = first_subplot_index + group_index;
        handle_groups(fig, group_mask, subplot_index, group_hover_prefix,
            additional_hover_text);

        if (first_subplot_index == 1) {
            std::string x_ref;
            std::string y_ref;
            if (subplot_index == 1) {
                x_ref = "x domain";
                y_ref = "y domain";
            } else {
                x_ref = fmt::format("x{} domain", subplot_index);
                y_ref = fmt::format("y{} domain", subplot_index);
            }
            auto annotation = fig.layout().add_annotation();
            annotation.x_ref(x_ref);
            annotation.y_ref(y_ref);
            annotation.x(annotation_center);
            annotation.y(annotation_end);
            annotation.y_shift(annotation_shift);
            annotation.show_arrow(false);
            annotation.align("center");
            annotation.text(group_name);
        }
    }

    fig.layout().grid().columns(group_values.size());

    return group_values.size();
}

void figure_builder_base::handle_groups(figure& fig,
    const std::vector<bool>& parent_mask, std::size_t subplot_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    if (group_.empty()) {
        const std::string group_name;
        constexpr std::size_t group_index = 0;
        add_trace(fig, parent_mask, subplot_index, group_name, group_index,
            hover_prefix, additional_hover_text);
        fig.layout().show_legend(false);
        return;
    }

    const auto grouping = data_.at(group_)->generate_group();
    const auto& group_values = grouping.first;
    const auto& group_indices = grouping.second;

    std::vector<bool> group_mask(group_indices.size(), false);
    for (std::size_t group_index = 0; group_index < group_values.size();
        ++group_index) {
        for (std::size_t row_index = 0; row_index < group_indices.size();
            ++row_index) {
            group_mask[row_index] = parent_mask[row_index] &&
                (group_indices[row_index] == group_index);
        }

        const auto& group_name = group_values[group_index];
        const auto group_hover_prefix =
            fmt::format("{}{}={}<br>", hover_prefix, group_, group_name);
        add_trace(fig, group_mask, subplot_index, group_name, group_index,
            group_hover_prefix, additional_hover_text);
    }

    fig.layout().legend().title().text(group_);
}

void figure_builder_base::configure_figure(figure& fig,
    std::size_t num_subplot_rows, std::size_t num_subplot_columns) const {
    configure_axes(fig, num_subplot_rows, num_subplot_columns);
    if (title_.empty()) {
        fig.layout().title().text(default_title());
    } else {
        fig.layout().title().text(title_);
    }
}

std::vector<std::string> figure_builder_base::generate_additional_hover_text()
    const {
    std::vector<std::string> hover_columns = additional_hover_data_in_trace();
    hover_columns.insert(
        hover_columns.end(), hover_data_.begin(), hover_data_.end());

    const std::size_t rows = data_.rows();
    std::vector<std::string> additional_hover_text(rows);
    for (const std::string& column_name : hover_columns) {
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
