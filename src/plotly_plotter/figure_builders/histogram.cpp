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
 * \brief Implementation of histogram class.
 */
#include "plotly_plotter/figure_builders/histogram.h"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include <fmt/format.h>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/figure_builders/details/calculate_axis_range.h"
#include "plotly_plotter/figure_builders/details/figure_builder_helper.h"
#include "plotly_plotter/figure_builders/figure_builder_base.h"
#include "plotly_plotter/layout.h"

namespace plotly_plotter::figure_builders {

histogram::histogram(const data_table& data) : figure_builder_base(data) {}

histogram& histogram::x(std::string value) {
    x_ = std::move(value);
    return *this;
}

histogram& histogram::y(std::string value) {
    y_ = std::move(value);
    return *this;
}

histogram& histogram::group(std::string value) {
    set_group(std::move(value));
    return *this;
}

histogram& histogram::subplot_row(std::string value) {
    set_subplot_row(std::move(value));
    return *this;
}

histogram& histogram::subplot_column(std::string value) {
    set_subplot_column(std::move(value));
    return *this;
}

histogram& histogram::animation_frame(std::string value) {
    set_animation_frame(std::move(value));
    return *this;
}

histogram& histogram::color_sequence(std::vector<std::string> value) {
    if (value.empty()) {
        throw std::runtime_error("Color sequence must not be empty.");
    }
    color_sequence_ = std::move(value);
    color_mode_ = color_mode::sequence;
    return *this;
}

histogram& histogram::fixed_color(std::string value) {
    fixed_color_ = std::move(value);
    color_mode_ = color_mode::fixed;
    return *this;
}

histogram& histogram::change_color_by_group() {
    color_mode_ = color_mode::sequence;
    return *this;
}

histogram& histogram::color_map(
    std::unordered_map<std::string, std::string> value) {
    color_map_ = std::move(value);
    color_mode_ = color_mode::map;
    return *this;
}

histogram& histogram::bin_width_method(
    utils::histogram_bin_width_method value) {
    bin_width_method_ = value;
    return *this;
}

histogram& histogram::title(std::string value) {
    set_title(std::move(value));
    return *this;
}

void histogram::configure_axes(figure& fig, std::size_t num_subplot_rows,
    std::size_t num_subplot_columns, bool require_manual_axis_ranges) const {
    details::configure_axes_common(
        fig, num_subplot_rows, num_subplot_columns, x_, y_);

    if (require_manual_axis_ranges) {
        constexpr double extended_factor = 0.0;
        if (!x_.empty() && data().at(x_)->is_numeric()) {
            const auto [min_x, max_x] = details::calculate_axis_range(
                data(), x_, extended_factor, false);
            for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
                ++i) {
                const std::size_t index = i + 1;
                fig.layout().xaxis(index).range(min_x, max_x);
            }
        }
        if (!y_.empty() && data().at(y_)->is_numeric()) {
            const auto [min_y, max_y] = details::calculate_axis_range(
                data(), y_, extended_factor, false);
            for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
                ++i) {
                const std::size_t index = i + 1;
                fig.layout().yaxis(index).range(min_y, max_y);
            }
        }
    }
}

std::string histogram::default_title() const {
    if (x_.empty()) {
        return y_;
    }
    return x_;
}

void histogram::add_trace(figure_frame_base& figure,
    const std::vector<bool>& parent_mask, std::size_t subplot_index,
    std::string_view group_name, std::size_t group_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    auto histogram = figure.add_histogram();
    if (!x_.empty() && !y_.empty()) {
        throw std::invalid_argument("Both x and y is set.");
    }
    if (x_.empty() && y_.empty()) {
        throw std::invalid_argument("Either x or y must be set.");
    }
    if (!x_.empty()) {
        histogram.x(filter_data_column(*data().at(x_), parent_mask));
    }
    if (!y_.empty()) {
        histogram.y(filter_data_column(*data().at(y_), parent_mask));
    }

    const bool has_additional_hover_text = !additional_hover_text.empty() &&
        !additional_hover_text.front().empty();
    if (has_additional_hover_text) {
        details::add_hover_text(histogram, parent_mask, additional_hover_text);
    }

    switch (color_mode_) {
    case color_mode::fixed:
        histogram.marker().color(fixed_color_);
        break;
    case color_mode::sequence:
        histogram.marker().color(
            color_sequence_[group_index % color_sequence_.size()]);
        break;
    case color_mode::map: {
        const auto iter = color_map_.find(std::string(group_name));
        if (iter == color_map_.end()) {
            throw std::runtime_error(fmt::format(
                "Color map does not contain group name: {}", group_name));
        }
        histogram.marker().color(iter->second);
        break;
    }
    }

    histogram.name(group_name);
    histogram.legend_group(group_name);

    auto hover_template = static_cast<std::string>(hover_prefix);
    hover_template += "(%{x}, %{y})";
    if (has_additional_hover_text) {
        hover_template += "%{text}";
    }
    histogram.hover_template(hover_template);

    if (subplot_index > 1) {
        histogram.xaxis(fmt::format("x{}", subplot_index));
        histogram.yaxis(fmt::format("y{}", subplot_index));
        histogram.show_legend(false);
    }

    if (subplot_index == 1 && bin_width_method_) {
        if (!x_.empty()) {
            const auto [min, max] = data().at(x_)->get_range();
            histogram.x_bins().start(min);
            histogram.x_bins().end(max);
            histogram.x_bins().size(
                data().at(x_)->calculate_histogram_bin_width(
                    *bin_width_method_));
        }
        if (!y_.empty()) {
            const auto [min, max] = data().at(y_)->get_range();
            histogram.y_bins().start(min);
            histogram.y_bins().end(max);
            histogram.y_bins().size(
                data().at(y_)->calculate_histogram_bin_width(
                    *bin_width_method_));
        }
    }
}

std::vector<std::string> histogram::additional_hover_data_in_trace() const {
    return {};
}

}  // namespace plotly_plotter::figure_builders
