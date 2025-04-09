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

    if (!subplot_column_.empty()) {
        fig.layout().grid().rows(1);
        fig.layout().grid().columns(1);
        fig.layout().grid().pattern("coupled");
    }

    const std::vector<bool> parent_mask(data_.rows(), true);
    constexpr std::size_t yaxis_index = 1;
    constexpr std::string_view hover_prefix;
    const auto additional_hover_text = generate_additional_hover_text();
    handle_subplot_column(
        fig, parent_mask, yaxis_index, hover_prefix, additional_hover_text);

    configure_figure(fig);

    return fig;
}

figure_builder_base::figure_builder_base(const data_table& data)
    : data_(data) {}

void figure_builder_base::set_group(std::string value) {
    group_ = std::move(value);
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
constexpr double annotation_shift = 20;

}  // namespace

void figure_builder_base::handle_subplot_column(figure& fig,
    const std::vector<bool>& parent_mask, std::size_t yaxis_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    if (subplot_column_.empty()) {
        constexpr std::size_t xaxis_index = 1;
        handle_groups(fig, parent_mask, xaxis_index, yaxis_index, hover_prefix,
            additional_hover_text);
        return;
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
        const std::size_t xaxis_index = group_index + 1;
        handle_groups(fig, group_mask, xaxis_index, yaxis_index,
            group_hover_prefix, additional_hover_text);

        std::string x_ref;
        if (xaxis_index == 1) {
            x_ref = "x domain";
        } else {
            x_ref = fmt::format("x{} domain", xaxis_index);
        }
        std::string y_ref;
        if (yaxis_index == 1) {
            y_ref = "y domain";
        } else {
            y_ref = fmt::format("y{} domain", yaxis_index);
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

    fig.layout().grid().columns(group_values.size());
}

void figure_builder_base::handle_groups(figure& fig,
    const std::vector<bool>& parent_mask, std::size_t xaxis_index,
    std::size_t yaxis_index, std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    if (group_.empty()) {
        const std::string group_name;
        constexpr std::size_t group_index = 0;
        add_trace(fig, parent_mask, xaxis_index, yaxis_index, group_name,
            group_index, hover_prefix, additional_hover_text);
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
        add_trace(fig, group_mask, xaxis_index, yaxis_index, group_name,
            group_index, group_hover_prefix, additional_hover_text);
    }

    fig.layout().legend().title().text(group_);
}

void figure_builder_base::configure_figure(figure& fig) const {
    std::size_t num_xaxes = 1;
    std::size_t num_yaxes = 1;
    if (!subplot_column_.empty()) {
        const auto grouping = data_.at(subplot_column_)->generate_group();
        num_xaxes = grouping.first.size();
    }
    configure_axes(fig, num_xaxes, num_yaxes);
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
