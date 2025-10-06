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
 * \brief Implementation of bar class.
 */
#include "plotly_plotter/figure_builders/bar.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <fmt/format.h>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/figure_builders/details/calculate_axis_range.h"
#include "plotly_plotter/figure_builders/details/figure_builder_helper.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/bar.h"

namespace plotly_plotter::figure_builders {

bar::bar(const data_table& data) : figure_builder_base(data) {}

bar& bar::x(std::string value) {
    x_ = std::move(value);
    return *this;
}

bar& bar::y(std::string value) {
    y_ = std::move(value);
    return *this;
}

bar& bar::group(std::string value) {
    set_group(std::move(value));
    return *this;
}

bar& bar::subplot_row(std::string value) {
    set_subplot_row(std::move(value));
    return *this;
}

bar& bar::subplot_column(std::string value) {
    set_subplot_column(std::move(value));
    return *this;
}

bar& bar::animation_frame(std::string value) {
    set_animation_frame(std::move(value));
    return *this;
}

bar& bar::hover_data(std::vector<std::string> value) {
    set_hover_data(std::move(value));
    return *this;
}

bar& bar::color_sequence(std::vector<std::string> value) {
    if (value.empty()) {
        throw std::runtime_error("Color sequence must not be empty.");
    }
    color_sequence_ = std::move(value);
    color_mode_ = color_mode::sequence;
    return *this;
}

bar& bar::fixed_color(std::string value) {
    fixed_color_ = std::move(value);
    color_mode_ = color_mode::fixed;
    return *this;
}

bar& bar::change_color_by_group() {
    color_mode_ = color_mode::sequence;
    return *this;
}

bar& bar::color_map(std::unordered_map<std::string, std::string> value) {
    color_map_ = std::move(value);
    color_mode_ = color_mode::map;
    return *this;
}

bar& bar::log_x(bool value) {
    log_x_ = value;
    return *this;
}

bar& bar::log_y(bool value) {
    log_y_ = value;
    return *this;
}

bar& bar::title(std::string value) {
    set_title(std::move(value));
    return *this;
}

void bar::configure_axes(figure& fig, std::size_t num_subplot_rows,
    std::size_t num_subplot_columns, bool require_manual_axis_ranges) const {
    details::configure_axes_common(
        fig, num_subplot_rows, num_subplot_columns, x_, y_);

    // Set log scale.
    if (log_x_) {
        for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
            ++i) {
            const std::size_t index = i + 1;
            fig.layout().xaxis(index).type("log");
        }
    }
    if (log_y_) {
        for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
            ++i) {
            const std::size_t index = i + 1;
            fig.layout().yaxis(index).type("log");
        }
    }

    // Set axis ranges.
    if (require_manual_axis_ranges || log_x_) {
        constexpr double extended_factor = 0.1;
        if (!x_.empty() && data().at(x_)->is_numeric()) {
            const auto [min_x, max_x] = details::calculate_axis_range(
                data(), x_, extended_factor, log_x_);
            for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
                ++i) {
                const std::size_t index = i + 1;
                fig.layout().xaxis(index).range(min_x, max_x);
            }
        }

        const auto [min_value, max_value] =
            details::calculate_axis_range(data(), y_, extended_factor, log_y_);
        for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
            ++i) {
            const std::size_t index = i + 1;
            fig.layout().yaxis(index).range(min_value, max_value);
        }
    }
}

std::string bar::default_title() const { return y_; }

void bar::add_trace(figure_frame_base& figure,
    const std::vector<bool>& parent_mask, std::size_t subplot_index,
    std::string_view group_name, std::size_t group_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    auto bar = figure.add_bar();

    if (!x_.empty()) {
        bar.x(filter_data_column(*data().at(x_), parent_mask));
    }

    if (y_.empty()) {
        throw std::runtime_error("y coordinates must be set.");
    }
    bar.y(filter_data_column(*data().at(y_), parent_mask));

    const bool has_additional_hover_text = !additional_hover_text.empty() &&
        !additional_hover_text.front().empty();
    if (has_additional_hover_text) {
        details::add_hover_text(bar, parent_mask, additional_hover_text);
    }

    switch (color_mode_) {
    case color_mode::fixed:
        bar.marker().color(fixed_color_);
        break;
    case color_mode::sequence:
        bar.marker().color(
            color_sequence_[group_index % color_sequence_.size()]);
        break;
    case color_mode::map: {
        const auto iter = color_map_.find(std::string(group_name));
        if (iter == color_map_.end()) {
            throw std::runtime_error(fmt::format(
                "Color map does not contain group name: {}", group_name));
        }
        bar.marker().color(iter->second);
        break;
    }
    }

    bar.name(group_name);
    bar.legend_group(group_name);

    auto hover_template = static_cast<std::string>(hover_prefix);
    if (!x_.empty()) {
        hover_template += fmt::format("{}=%{{x}}<br>", x_);
    }
    hover_template += fmt::format("{}=%{{y}}", y_);
    if (has_additional_hover_text) {
        hover_template += "%{text}";
    }
    bar.hover_template(hover_template);

    if (subplot_index > 1) {
        bar.xaxis(fmt::format("x{}", subplot_index));
        bar.yaxis(fmt::format("y{}", subplot_index));
        bar.show_legend(false);
    }

    if (group_index > 0 && !x_.empty()) {
        figure.layout().bar_mode("group");
    } else {
        figure.layout().bar_mode("overlay");
    }
}

std::vector<std::string> bar::additional_hover_data_in_trace() const {
    return {};
}

}  // namespace plotly_plotter::figure_builders
