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
 * \brief Implementation of violin class.
 */
#include "plotly_plotter/figure_builders/violin.h"

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <fmt/format.h>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/figure_builders/details/figure_builder_helper.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/violin.h"

namespace plotly_plotter::figure_builders {

violin::violin(const data_table& data) : figure_builder_base(data) {}

violin& violin::x(std::string value) {
    x_ = std::move(value);
    return *this;
}

violin& violin::y(std::string value) {
    y_ = std::move(value);
    return *this;
}

violin& violin::group(std::string value) {
    set_group(std::move(value));
    return *this;
}

violin& violin::subplot_row(std::string value) {
    set_subplot_row(std::move(value));
    return *this;
}

violin& violin::subplot_column(std::string value) {
    set_subplot_column(std::move(value));
    return *this;
}

violin& violin::animation_frame(std::string value) {
    set_animation_frame(std::move(value));
    return *this;
}

violin& violin::hover_data(std::vector<std::string> value) {
    set_hover_data(std::move(value));
    return *this;
}

violin& violin::color_sequence(std::vector<std::string> value) {
    if (value.empty()) {
        throw std::runtime_error("Color sequence must not be empty.");
    }
    color_sequence_ = std::move(value);
    return *this;
}

violin& violin::fixed_color(std::string value) {
    fixed_color_ = std::move(value);
    color_mode_ = color_mode::fixed;
    return *this;
}

violin& violin::change_color_by_group() {
    color_mode_ = color_mode::sequence;
    return *this;
}

violin& violin::color_map(std::unordered_map<std::string, std::string> value) {
    color_map_ = std::move(value);
    color_mode_ = color_mode::map;
    return *this;
}

violin& violin::show_box(bool value) {
    show_box_ = value;
    return *this;
}

violin& violin::show_mean_line(bool value) {
    show_mean_line_ = value;
    return *this;
}

violin& violin::points(std::string value) {
    points_ = std::move(value);
    return *this;
}

violin& violin::log_y(bool value) {
    log_y_ = value;
    return *this;
}

violin& violin::title(std::string value) {
    set_title(std::move(value));
    return *this;
}

void violin::configure_axes(figure& fig, std::size_t num_subplot_rows,
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
        const auto [min, max] = data().at(y_)->get_positive_range();
        const double min_log = std::log10(min);
        const double max_log = std::log10(max);
        const double range_log = max_log - min_log;
        constexpr double extended_factor = 0.1;
        const double min_log_extended = min_log - extended_factor * range_log;
        const double max_log_extended = max_log + extended_factor * range_log;

        for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
            ++i) {
            const std::size_t index = i + 1;
            fig.layout().yaxis(index).type("log");
            fig.layout().yaxis(index).range(min_log_extended, max_log_extended);
        }
    }
}

std::string violin::default_title() const { return y_; }

void violin::add_trace(figure_frame_base& figure,
    const std::vector<bool>& parent_mask, std::size_t subplot_index,
    std::string_view group_name, std::size_t group_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    auto violin = figure.add_violin();

    if (!x_.empty()) {
        violin.x(filter_data_column(*data().at(x_), parent_mask));
    }

    if (y_.empty()) {
        throw std::runtime_error("y coordinates must be set.");
    }
    violin.y(filter_data_column(*data().at(y_), parent_mask));

    const bool has_additional_hover_text = !additional_hover_text.empty() &&
        !additional_hover_text.front().empty();
    if (has_additional_hover_text) {
        details::add_hover_text(violin, parent_mask, additional_hover_text);
    }

    switch (color_mode_) {
    case color_mode::fixed:
        violin.color(fixed_color_);
        break;
    case color_mode::sequence:
        violin.color(color_sequence_[group_index % color_sequence_.size()]);
        break;
    case color_mode::map: {
        const auto iter = color_map_.find(std::string(group_name));
        if (iter == color_map_.end()) {
            throw std::runtime_error(fmt::format(
                "Color map does not contain group name: {}", group_name));
        }
        violin.color(iter->second);
        break;
    }
    }

    violin.box().visible(show_box_);
    violin.mean_line().visible(show_mean_line_);
    violin.points(points_);

    violin.name(group_name);
    violin.legend_group(group_name);

    auto hover_template = static_cast<std::string>(hover_prefix);
    if (!x_.empty()) {
        hover_template += fmt::format("{}=%{{x}}<br>", x_);
    }
    hover_template += fmt::format("{}=%{{y}}", y_);
    if (has_additional_hover_text) {
        hover_template += "%{text}";
    }
    violin.hover_template(hover_template);

    if (subplot_index > 1) {
        violin.xaxis(fmt::format("x{}", subplot_index));
        violin.yaxis(fmt::format("y{}", subplot_index));
        violin.show_legend(false);
    }

    if (group_index > 0 && !x_.empty()) {
        figure.layout().violin_mode("group");
    }
}

std::vector<std::string> violin::additional_hover_data_in_trace() const {
    return {};
}

}  // namespace plotly_plotter::figure_builders
