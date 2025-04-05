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

#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

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

scatter& scatter::mode(std::string value) {
    mode_ = std::move(value);
    return *this;
}

scatter& scatter::title(std::string value) {
    set_title(std::move(value));
    return *this;
}

void scatter::configure_axes(figure& fig) const {
    if (!x_.empty()) {
        fig.layout().xaxis().title().text(x_);
    }
    fig.layout().yaxis().title().text(y_);
}

std::string scatter::default_title() const { return y_; }

void scatter::add_trace_without_grouping(figure& fig) const {
    auto scatter = fig.add_scatter();
    scatter.mode(mode_);
    if (!x_.empty()) {
        scatter.x(*data().at(x_));
    }
    if (y_.empty()) {
        throw std::runtime_error("y coordinates must be set.");
    }
    scatter.y(*data().at(y_));
}

void scatter::add_trace_for_group(figure& figure,
    const std::vector<bool>& group_mask, std::string_view group_name) const {
    auto scatter = figure.add_scatter();
    scatter.mode(mode_);
    if (!x_.empty()) {
        scatter.x(filter_data_column(*data().at(x_), group_mask));
    }
    if (y_.empty()) {
        throw std::runtime_error("y coordinates must be set.");
    }
    scatter.y(filter_data_column(*data().at(y_), group_mask));
    scatter.name(group_name);
}

}  // namespace plotly_plotter::figure_builders
