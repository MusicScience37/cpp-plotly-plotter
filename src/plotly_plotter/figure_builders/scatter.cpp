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

scatter& scatter::group(std::string value) {
    set_group(std::move(value));
    return *this;
}

scatter& scatter::subplot_column(std::string value) {
    set_subplot_column(std::move(value));
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

scatter& scatter::use_web_gl(bool value) {
    use_web_gl_ = value;
    return *this;
}

scatter& scatter::title(std::string value) {
    set_title(std::move(value));
    return *this;
}

void scatter::configure_axes(
    figure& fig, std::size_t num_xaxes, std::size_t num_yaxes) const {
    if (!x_.empty()) {
        for (std::size_t i = 0; i < num_xaxes; ++i) {
            fig.layout().xaxis(i + 1).title().text(x_);
            if (i > 0) {
                fig.layout().xaxis(i + 1).matches("x");
            }
        }
    }
    for (std::size_t i = 0; i < num_yaxes; ++i) {
        fig.layout().yaxis(i + 1).title().text(y_);
        if (i > 0) {
            fig.layout().yaxis(i + 1).matches("y");
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

void scatter::add_trace(figure& figure, const std::vector<bool>& parent_mask,
    std::size_t xaxis_index, std::size_t yaxis_index,
    std::string_view group_name, std::size_t group_index,
    std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    const std::size_t rows = data().rows();
    const bool use_web_gl =
        use_web_gl_.value_or(rows >= max_rows_for_non_gl_trace);
    if (!use_web_gl) {
        auto scatter = figure.add_scatter();
        configure_trace(scatter, parent_mask, xaxis_index, yaxis_index,
            group_name, group_index, hover_prefix, additional_hover_text);
    } else {
        auto scatter = figure.add_scatter_gl();
        configure_trace(scatter, parent_mask, xaxis_index, yaxis_index,
            group_name, group_index, hover_prefix, additional_hover_text);
    }
}

template <typename Trace>
void scatter::configure_trace(Trace& scatter,
    const std::vector<bool>& parent_mask, std::size_t xaxis_index,
    std::size_t yaxis_index, std::string_view group_name,
    std::size_t group_index, std::string_view hover_prefix,
    const std::vector<std::string>& additional_hover_text) const {
    scatter.mode(mode_);

    if (!x_.empty()) {
        scatter.x(filter_data_column(*data().at(x_), parent_mask));
    }

    if (y_.empty()) {
        throw std::runtime_error("y coordinates must be set.");
    }
    scatter.y(filter_data_column(*data().at(y_), parent_mask));

    const bool has_additional_hover_text = !additional_hover_text.empty() &&
        !additional_hover_text.front().empty();
    if (has_additional_hover_text) {
        std::vector<std::string> additional_hover_text_filtered;
        additional_hover_text_filtered.reserve(additional_hover_text.size());
        for (std::size_t row_index = 0; row_index < parent_mask.size();
            ++row_index) {
            if (parent_mask[row_index]) {
                additional_hover_text_filtered.push_back(
                    additional_hover_text[row_index]);
            }
        }
        scatter.text(additional_hover_text_filtered);
    }

    scatter.color(color_sequence_[group_index % color_sequence_.size()]);

    scatter.name(group_name);

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

    if (xaxis_index > 1) {
        scatter.xaxis(fmt::format("x{}", xaxis_index));
        scatter.show_legend(false);
    }
    if (yaxis_index > 1) {
        scatter.yaxis(fmt::format("y{}", yaxis_index));
        scatter.show_legend(false);
    }
}

}  // namespace plotly_plotter::figure_builders
