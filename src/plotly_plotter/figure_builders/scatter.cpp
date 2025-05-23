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
 * \brief Implementation of scatter class.
 */
#include "plotly_plotter/figure_builders/scatter.h"

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
#include "plotly_plotter/traces/scatter.h"

namespace plotly_plotter::figure_builders {

scatter::scatter(const data_table& data) : figure_builder_base(data) {}

scatter& scatter::x(std::string value) {
    x_ = std::move(value);
    return *this;
}

scatter& scatter::y(std::string value) {
    y_ = std::move(value);
    return *this;
}

scatter& scatter::error_x(std::string value) {
    error_x_ = std::move(value);
    return *this;
}

scatter& scatter::error_y(std::string value) {
    error_y_ = std::move(value);
    return *this;
}

scatter& scatter::error_x_minus(std::string value) {
    error_x_minus_ = std::move(value);
    return *this;
}

scatter& scatter::error_y_minus(std::string value) {
    error_y_minus_ = std::move(value);
    return *this;
}

scatter& scatter::marker_color(std::string value) {
    marker_color_ = std::move(value);
    return *this;
}

scatter& scatter::group(std::string value) {
    set_group(std::move(value));
    return *this;
}

scatter& scatter::subplot_row(std::string value) {
    set_subplot_row(std::move(value));
    return *this;
}

scatter& scatter::subplot_column(std::string value) {
    set_subplot_column(std::move(value));
    return *this;
}

scatter& scatter::animation_frame(std::string value) {
    set_animation_frame(std::move(value));
    return *this;
}

scatter& scatter::hover_data(std::vector<std::string> value) {
    set_hover_data(std::move(value));
    return *this;
}

scatter& scatter::mode(std::string value) {
    mode_ = std::move(value);
    return *this;
}

scatter& scatter::log_x(bool value) {
    log_x_ = value;
    return *this;
}

scatter& scatter::log_y(bool value) {
    log_y_ = value;
    return *this;
}

scatter& scatter::color_sequence(std::vector<std::string> value) {
    if (value.empty()) {
        throw std::runtime_error("Color sequence must not be empty.");
    }
    color_sequence_ = std::move(value);
    color_mode_ = color_mode::sequence;
    return *this;
}

scatter& scatter::fixed_color(std::string value) {
    fixed_color_ = std::move(value);
    color_mode_ = color_mode::fixed;
    return *this;
}

scatter& scatter::change_color_by_group() {
    color_mode_ = color_mode::sequence;
    return *this;
}

scatter& scatter::color_map(
    std::unordered_map<std::string, std::string> value) {
    color_map_ = std::move(value);
    color_mode_ = color_mode::map;
    return *this;
}

scatter& scatter::dash_sequence(std::vector<std::string> value) {
    if (value.empty()) {
        throw std::runtime_error("Dash sequence must not be empty.");
    }
    dash_sequence_ = std::move(value);
    dash_mode_ = dash_mode::sequence;
    return *this;
}

scatter& scatter::fixed_dash(std::string value) {
    fixed_dash_ = std::move(value);
    dash_mode_ = dash_mode::fixed;
    return *this;
}

scatter& scatter::change_dash_by_group() {
    dash_mode_ = dash_mode::sequence;
    return *this;
}

scatter& scatter::dash_map(std::unordered_map<std::string, std::string> value) {
    dash_map_ = std::move(value);
    dash_mode_ = dash_mode::map;
    return *this;
}

scatter& scatter::use_web_gl(bool value) {
    use_web_gl_ = value;
    return *this;
}

scatter& scatter::title(std::string value) {
    set_title(std::move(value));
    return *this;
}

void scatter::configure_axes(figure& fig, std::size_t num_subplot_rows,
    std::size_t num_subplot_columns, bool require_manual_axis_ranges) const {
    details::configure_axes_common(
        fig, num_subplot_rows, num_subplot_columns, x_, y_);

    // Set log scale.
    for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns; ++i) {
        const std::size_t index = i + 1;
        if (log_x_) {
            fig.layout().xaxis(index).type("log");
        }
        if (log_y_) {
            fig.layout().yaxis(index).type("log");
        }
    }

    if (!marker_color_.empty()) {
        fig.layout().color_axis().show_scale(true);
        fig.layout().color_axis().color_bar().title().text(marker_color_);
    }

    // Set axis ranges.
    if (require_manual_axis_ranges) {
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
        const auto [min_y, max_y] =
            details::calculate_axis_range(data(), y_, extended_factor, log_y_);
        for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
            ++i) {
            const std::size_t index = i + 1;
            fig.layout().yaxis(index).range(min_y, max_y);
        }
    }
}

std::string scatter::default_title() const { return y_; }

// clang-format off
/*!
 * \brief The maximum number of rows for non-WebGL traces.
 *
 * \note This number is written in the document of
 * [plotly.express.scatter function](https://plotly.com/python-api-reference/generated/plotly.express.scatter)
 * in Plotly Python library.
 */
constexpr std::size_t max_rows_for_non_gl_trace = 1000;
// clang-format on

void scatter::add_trace(figure_frame_base& figure,
    const std::vector<bool>& parent_mask, std::size_t subplot_index,
    std::string_view group_name, std::size_t group_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    const std::size_t rows = data().rows();
    const bool use_web_gl =
        use_web_gl_.value_or(rows >= max_rows_for_non_gl_trace);
    if (!use_web_gl) {
        auto scatter = figure.add_scatter();
        configure_trace(scatter, parent_mask, subplot_index, group_name,
            group_index, hover_prefix, additional_hover_text);
    } else {
        auto scatter = figure.add_scatter_gl();
        configure_trace(scatter, parent_mask, subplot_index, group_name,
            group_index, hover_prefix, additional_hover_text);
    }
}

template <typename Trace>
void scatter::configure_trace(Trace& scatter,
    const std::vector<bool>& parent_mask, std::size_t subplot_index,
    std::string_view group_name, std::size_t group_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    scatter.mode(mode_);

    if (!x_.empty()) {
        scatter.x(filter_data_column(*data().at(x_), parent_mask));
    }

    if (y_.empty()) {
        throw std::runtime_error("y coordinates must be set.");
    }
    scatter.y(filter_data_column(*data().at(y_), parent_mask));

    if (!error_x_.empty()) {
        scatter.error_x().array(
            filter_data_column(*data().at(error_x_), parent_mask));
        if (!error_x_minus_.empty()) {
            scatter.error_x().array_minus(
                filter_data_column(*data().at(error_x_minus_), parent_mask));
            scatter.error_x().symmetric(false);
        } else {
            scatter.error_x().symmetric(true);
        }
        scatter.error_x().type("data");
        scatter.error_x().visible(true);
    }

    if (!error_y_.empty()) {
        scatter.error_y().array(
            filter_data_column(*data().at(error_y_), parent_mask));
        if (!error_y_minus_.empty()) {
            scatter.error_y().array_minus(
                filter_data_column(*data().at(error_y_minus_), parent_mask));
            scatter.error_y().symmetric(false);
        } else {
            scatter.error_y().symmetric(true);
        }
        scatter.error_y().type("data");
        scatter.error_y().visible(true);
    }

    const bool has_additional_hover_text = !additional_hover_text.empty() &&
        !additional_hover_text.front().empty();
    if (has_additional_hover_text) {
        details::add_hover_text(scatter, parent_mask, additional_hover_text);
    }

    if (marker_color_.empty()) {
        switch (color_mode_) {
        case color_mode::fixed:
            scatter.color(fixed_color_);
            break;
        case color_mode::sequence:
            scatter.color(
                color_sequence_[group_index % color_sequence_.size()]);
            break;
        case color_mode::map: {
            const auto iter = color_map_.find(std::string(group_name));
            if (iter == color_map_.end()) {
                throw std::runtime_error(fmt::format(
                    "Color map does not contain group name: {}", group_name));
            }
            scatter.color(iter->second);
            break;
        }
        }
    } else {
        scatter.marker().color(
            filter_data_column(*data().at(marker_color_), parent_mask));
        scatter.marker().color_axis("coloraxis");
    }

    switch (dash_mode_) {
    case dash_mode::fixed:
        scatter.line().dash(fixed_dash_);
        break;
    case dash_mode::sequence:
        scatter.line().dash(
            dash_sequence_[group_index % dash_sequence_.size()]);
        break;
    case dash_mode::map: {
        const auto iter = dash_map_.find(std::string(group_name));
        if (iter == dash_map_.end()) {
            throw std::runtime_error(fmt::format(
                "Dash map does not contain group name: {}", group_name));
        }
        scatter.line().dash(iter->second);
        break;
    }
    }

    scatter.name(group_name);
    scatter.legend_group(group_name);

    auto hover_template = static_cast<std::string>(hover_prefix);
    if (x_.empty()) {
        hover_template += "index=%{x}<br>";
    } else {
        hover_template += fmt::format("{}=%{{x}}<br>", x_);
    }
    hover_template += fmt::format("{}=%{{y}}", y_);
    if (has_additional_hover_text) {
        hover_template += "%{text}";
    }
    scatter.hover_template(hover_template);

    if (subplot_index > 1) {
        scatter.xaxis(fmt::format("x{}", subplot_index));
        scatter.yaxis(fmt::format("y{}", subplot_index));
        scatter.show_legend(false);
    }
}

std::vector<std::string> scatter::additional_hover_data_in_trace() const {
    std::vector<std::string> result;
    if (!marker_color_.empty()) {
        result.push_back(marker_color_);
    }
    return result;
}

}  // namespace plotly_plotter::figure_builders
