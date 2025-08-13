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
 * \brief Implementation of bar_based_histogram class.
 */
#include "plotly_plotter/figure_builders/bar_based_histogram.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/figure_builders/details/calculate_axis_range.h"
#include "plotly_plotter/figure_builders/details/figure_builder_helper.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/utils/calculate_histogram_bin_width.h"

namespace plotly_plotter::figure_builders {

bar_based_histogram::bar_based_histogram(const data_table& data)
    : figure_builder_base(data) {}

bar_based_histogram& bar_based_histogram::x(std::string value) {
    x_ = std::move(value);
    return *this;
}

bar_based_histogram& bar_based_histogram::group(std::string value) {
    set_group(std::move(value));
    return *this;
}

bar_based_histogram& bar_based_histogram::subplot_row(std::string value) {
    set_subplot_row(std::move(value));
    return *this;
}

bar_based_histogram& bar_based_histogram::subplot_column(std::string value) {
    set_subplot_column(std::move(value));
    return *this;
}

bar_based_histogram& bar_based_histogram::animation_frame(std::string value) {
    set_animation_frame(std::move(value));
    return *this;
}

bar_based_histogram& bar_based_histogram::color_sequence(
    std::vector<std::string> value) {
    if (value.empty()) {
        throw std::runtime_error("Color sequence must not be empty.");
    }
    color_sequence_ = std::move(value);
    color_mode_ = color_mode::sequence;
    return *this;
}

bar_based_histogram& bar_based_histogram::fixed_color(std::string value) {
    fixed_color_ = std::move(value);
    color_mode_ = color_mode::fixed;
    return *this;
}

bar_based_histogram& bar_based_histogram::change_color_by_group() {
    color_mode_ = color_mode::sequence;
    return *this;
}

bar_based_histogram& bar_based_histogram::color_map(
    std::unordered_map<std::string, std::string> value) {
    color_map_ = std::move(value);
    color_mode_ = color_mode::map;
    return *this;
}

bar_based_histogram& bar_based_histogram::log_x(bool value) {
    log_x_ = value;
    return *this;
}

bar_based_histogram& bar_based_histogram::bin_width_method(
    utils::histogram_bin_width_method value) {
    bin_width_method_ = value;
    fixed_bin_width_.reset();
    return *this;
}

bar_based_histogram& bar_based_histogram::fixed_bin_width(double value) {
    fixed_bin_width_ = value;
    return *this;
}

bar_based_histogram& bar_based_histogram::title(std::string value) {
    set_title(std::move(value));
    return *this;
}

void bar_based_histogram::configure_axes(figure& fig,
    std::size_t num_subplot_rows, std::size_t num_subplot_columns,
    bool require_manual_axis_ranges) const {
    (void)require_manual_axis_ranges;

    details::configure_axes_common(
        fig, num_subplot_rows, num_subplot_columns, x_, "Count");

    if (log_x_) {
        for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns;
            ++i) {
            fig.layout().xaxis(i + 1).type("log");
        }
    }

    constexpr double x_extended_factor = 0.0;
    constexpr double y_extended_factor = 0.1;
    const auto [min_x, max_x] =
        details::calculate_axis_range(data(), x_, x_extended_factor, log_x_);
    const double min_y = 0;
    const double max_y =
        static_cast<double>(max_bin_count_) * (1.0 + y_extended_factor);
    for (std::size_t i = 0; i < num_subplot_rows * num_subplot_columns; ++i) {
        const std::size_t index = i + 1;
        fig.layout().xaxis(index).range(min_x, max_x);
        fig.layout().yaxis(index).range(min_y, max_y);
    }
}

std::string bar_based_histogram::default_title() const { return x_; }

void bar_based_histogram::add_trace(figure_frame_base& figure,
    const std::vector<bool>& parent_mask, std::size_t subplot_index,
    std::string_view group_name, std::size_t group_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    // Histogram does not support additional hover text.
    (void)additional_hover_text;

    if (x_.empty()) {
        throw std::runtime_error("x coordinate is not set for histogram.");
    }

    calculate_bin_counts(parent_mask);

    auto bar = figure.add_bar();

    bar.x(bin_centers_);
    bar.width(bin_widths_);
    bar.y(bin_counts_);

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
    hover_template += "count=%{y}";
    bar.hover_template(hover_template);

    if (subplot_index > 1) {
        bar.xaxis(fmt::format("x{}", subplot_index));
        bar.yaxis(fmt::format("y{}", subplot_index));
        bar.show_legend(false);
    }

    // TODO Tune opacity.
    bar.opacity(0.8);  // NOLINT(*-magic-numbers)
    if (group_index > 0 && !x_.empty()) {
        figure.layout().bar_mode("overlay");
    }
}

std::vector<std::string> bar_based_histogram::additional_hover_data_in_trace()
    const {
    return {};
}

void bar_based_histogram::calculate_bin_edges() const {
    if (!bin_edges_.empty()) {
        // Already done.
        return;
    }

    if (log_x_) {
        if (!fixed_bin_width_) {
            auto all_values = data().at(x_)->as_double_vector();
            for (auto iter = all_values.begin(); iter != all_values.end();) {
                if (*iter <= 0.0) {
                    iter = all_values.erase(iter);
                } else {
                    *iter = std::log10(*iter);
                    ++iter;
                }
            }
            fixed_bin_width_ = utils::calculate_histogram_bin_width(
                all_values, bin_width_method_);
        }
        const double& log_bin_width = *fixed_bin_width_;

        const auto [min_value, max_value] = data().at(x_)->get_positive_range();
        const double log_min_value = std::log10(min_value);
        const double log_max_value = std::log10(max_value);
        const auto num_bins = std::max(
            static_cast<std::size_t>(
                std::ceil((log_max_value - log_min_value) / log_bin_width)),
            static_cast<std::size_t>(1));
        bin_edges_.resize(num_bins + 1);
        for (std::size_t i = 0; i <= num_bins; ++i) {
            const double log_bin_edge =
                log_min_value + static_cast<double>(i) * log_bin_width;
            // NOLINTNEXTLINE(*-magic-numbers)
            bin_edges_[i] = std::pow(10.0, log_bin_edge);
        }
        bin_centers_.resize(num_bins);
        bin_widths_.resize(num_bins);
        for (std::size_t i = 0; i < num_bins; ++i) {
            // NOLINTNEXTLINE(*-magic-numbers)
            bin_centers_[i] = (bin_edges_[i] + bin_edges_[i + 1]) * 0.5;
            bin_widths_[i] = bin_edges_[i + 1] - bin_edges_[i];
        }
    } else {
        if (!fixed_bin_width_) {
            const auto all_values = data().at(x_)->as_double_vector();
            fixed_bin_width_ = utils::calculate_histogram_bin_width(
                all_values, bin_width_method_);
        }
        const double& bin_width = *fixed_bin_width_;

        const auto [min_value, max_value] = data().at(x_)->get_range();
        const auto num_bins =
            std::max(static_cast<std::size_t>(
                         std::ceil((max_value - min_value) / bin_width)),
                static_cast<std::size_t>(1));
        bin_edges_.resize(num_bins + 1);
        for (std::size_t i = 0; i <= num_bins; ++i) {
            bin_edges_[i] = min_value + static_cast<double>(i) * bin_width;
        }
        bin_centers_.resize(num_bins);
        bin_widths_.resize(num_bins);
        for (std::size_t i = 0; i < num_bins; ++i) {
            // NOLINTNEXTLINE(*-magic-numbers)
            bin_centers_[i] = (bin_edges_[i] + bin_edges_[i + 1]) * 0.5;
            bin_widths_[i] = bin_edges_[i + 1] - bin_edges_[i];
        }
    }
}

void bar_based_histogram::calculate_bin_counts(
    const std::vector<bool>& mask) const {
    calculate_bin_edges();

    const auto values = data().at(x_)->as_masked_double_vector(mask);
    bin_counts_.resize(bin_centers_.size());
    std::fill(bin_counts_.begin(), bin_counts_.end(), 0);
    for (const double& value : values) {
        const auto bin_index = static_cast<std::size_t>(std::distance(
            bin_edges_.begin() + 1,
            std::lower_bound(bin_edges_.begin() + 1, bin_edges_.end(), value)));
        if (bin_index < bin_counts_.size()) {
            ++bin_counts_[bin_index];
        }
    }
    for (const auto& count : bin_counts_) {
        max_bin_count_ = std::max(max_bin_count_, count);
    }
}

}  // namespace plotly_plotter::figure_builders
