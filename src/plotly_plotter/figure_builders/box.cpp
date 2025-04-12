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
 * \brief Implementation of box class.
 */
#include "plotly_plotter/figure_builders/box.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <fmt/format.h>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/figure_builders/details/figure_builder_helper.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/box.h"

namespace plotly_plotter::figure_builders {

box::box(const data_table& data) : figure_builder_base(data) {}

box& box::x(std::string value) {
    x_ = std::move(value);
    return *this;
}

box& box::y(std::string value) {
    y_ = std::move(value);
    return *this;
}

box& box::group(std::string value) {
    set_group(std::move(value));
    return *this;
}

box& box::subplot_row(std::string value) {
    set_subplot_row(std::move(value));
    return *this;
}

box& box::subplot_column(std::string value) {
    set_subplot_column(std::move(value));
    return *this;
}

box& box::hover_data(std::vector<std::string> value) {
    set_hover_data(std::move(value));
    return *this;
}

box& box::color_sequence(std::vector<std::string> value) {
    if (value.empty()) {
        throw std::runtime_error("Color sequence must not be empty.");
    }
    color_sequence_ = std::move(value);
    color_mode_ = color_mode::sequence;
    return *this;
}

box& box::fixed_color(std::string value) {
    fixed_color_ = std::move(value);
    color_mode_ = color_mode::fixed;
    return *this;
}

box& box::change_color_by_group() {
    color_mode_ = color_mode::sequence;
    return *this;
}

box& box::color_map(std::unordered_map<std::string, std::string> value) {
    color_map_ = std::move(value);
    color_mode_ = color_mode::map;
    return *this;
}

box& box::box_mean(bool value) {
    box_mean_ = value;
    return *this;
}

box& box::box_mean(std::string value) {
    box_mean_ = std::move(value);
    return *this;
}

box& box::box_mean(const char* value) { return box_mean(std::string(value)); }

box& box::box_points(std::string value) {
    box_points_ = std::move(value);
    return *this;
}

box& box::log_y(bool value) {
    log_y_ = value;
    return *this;
}

box& box::title(std::string value) {
    set_title(std::move(value));
    return *this;
}

void box::configure_axes(figure& fig, std::size_t num_subplot_rows,
    std::size_t num_subplot_columns) const {
    details::configure_axes_common(
        fig, num_subplot_rows, num_subplot_columns, x_, y_);

    // Set x-axis to categorical.
    for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns; ++i) {
        const std::size_t index = i + 1;
        fig.layout().xaxis(index).type("category");
    }

    // Set log scale.
    if (log_y_) {
        for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
            ++i) {
            const std::size_t index = i + 1;
            fig.layout().yaxis(index).type("log");
        }
    }
}

std::string box::default_title() const { return y_; }

void box::add_trace(figure& figure, const std::vector<bool>& parent_mask,
    std::size_t subplot_index, std::string_view group_name,
    std::size_t group_index, std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    auto box = figure.add_box();

    if (!x_.empty()) {
        box.x(filter_data_column(*data().at(x_), parent_mask));
    }

    if (y_.empty()) {
        throw std::runtime_error("y coordinates must be set.");
    }
    box.y(filter_data_column(*data().at(y_), parent_mask));

    const bool has_additional_hover_text = !additional_hover_text.empty() &&
        !additional_hover_text.front().empty();
    if (has_additional_hover_text) {
        details::add_hover_text(box, parent_mask, additional_hover_text);
    }

    switch (color_mode_) {
    case color_mode::fixed:
        box.color(fixed_color_);
        break;
    case color_mode::sequence:
        box.color(color_sequence_[group_index % color_sequence_.size()]);
        break;
    case color_mode::map: {
        const auto iter = color_map_.find(std::string(group_name));
        if (iter == color_map_.end()) {
            throw std::runtime_error(fmt::format(
                "Color map does not contain group name: {}", group_name));
        }
        box.color(iter->second);
        break;
    }
    }

    std::visit([&box](const auto& value) { box.box_mean(value); }, box_mean_);
    box.box_points(box_points_);

    box.name(group_name);

    auto hover_template = static_cast<std::string>(hover_prefix);
    if (!x_.empty()) {
        hover_template += fmt::format("{}=%{{x}}<br>", x_);
    }
    hover_template += fmt::format("{}=%{{y}}", y_);
    if (has_additional_hover_text) {
        hover_template += "%{text}";
    }
    box.hover_template(hover_template);

    if (subplot_index > 1) {
        box.xaxis(fmt::format("x{}", subplot_index));
        box.yaxis(fmt::format("y{}", subplot_index));
        box.show_legend(false);
    }

    if (group_index > 0 && !x_.empty()) {
        figure.layout().box_mode("group");
    }
}

}  // namespace plotly_plotter::figure_builders
