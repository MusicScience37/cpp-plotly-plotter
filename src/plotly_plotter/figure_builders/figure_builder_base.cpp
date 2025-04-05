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
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"

namespace plotly_plotter::figure_builders {

figure figure_builder_base::create() const {
    if (group_.empty()) {
        return create_without_grouping();
    }
    return create_with_grouping();
}

figure_builder_base::figure_builder_base(const data_table& data)
    : data_(data) {}

void figure_builder_base::set_group(std::string value) {
    group_ = std::move(value);
}

void figure_builder_base::set_title(std::string value) {
    title_ = std::move(value);
}

const data_table& figure_builder_base::data() const noexcept { return data_; }

figure figure_builder_base::create_without_grouping() const {
    figure fig;

    add_trace_without_grouping(fig);

    configure_axes(fig);
    if (title_.empty()) {
        fig.layout().title().text(default_title());
    } else {
        fig.layout().title().text(title_);
    }

    return fig;
}

figure figure_builder_base::create_with_grouping() const {
    figure fig;

    const auto grouping = data_.at(group_)->generate_group();
    const auto& group_values = grouping.first;
    const auto& group_indices = grouping.second;

    std::vector<bool> group_mask(group_indices.size(), false);
    for (std::size_t group_index = 0; group_index < group_values.size();
        ++group_index) {
        for (std::size_t row_index = 0; row_index < group_indices.size();
            ++row_index) {
            group_mask[row_index] = (group_indices[row_index] == group_index);
        }

        const auto group_name =
            fmt::format("{}={}", group_, group_values[group_index]);
        add_trace_for_group(fig, group_mask, group_name);
    }

    configure_axes(fig);
    if (title_.empty()) {
        fig.layout().title().text(default_title());
    } else {
        fig.layout().title().text(title_);
    }

    return fig;
}

}  // namespace plotly_plotter::figure_builders
