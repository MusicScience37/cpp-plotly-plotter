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
 * \brief Definition of line class.
 */
#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/scatter.h"

namespace plotly_plotter::figure_builders {

/*!
 * \brief Class to create figures of line plots.
 *
 * \note This class hold the reference of the data.
 * So, the data must be valid until this object is destructed.
 * \note Objects of this class can't be reused.
 */
class line {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     *
     * \note This class hold the reference of the data.
     * So, the data must be valid until this object is destructed.
     */
    explicit line(const data_table& data) : data_(data) {}

    /*!
     * \brief Set the column name of x coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    line& x(std::string value) {
        x_ = std::move(value);
        return *this;
    }

    /*!
     * \brief Set the column name of y coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    line& y(std::string value) {
        y_ = std::move(value);
        return *this;
    }

    /*!
     * \brief Set the column name of groups.
     *
     * \param[in] value Value.
     * \return This object.
     */
    line& group(std::string value) {
        group_ = std::move(value);
        return *this;
    }

    /*!
     * \brief Set the title of the figure.
     *
     * \param[in] value Value.
     * \return This object.
     */
    line& title(std::string value) {
        title_ = std::move(value);
        return *this;
    }

    /*!
     * \brief Create a figure.
     *
     * \return Figure.
     */
    [[nodiscard]] figure create() const {
        if (group_.empty()) {
            return create_without_grouping();
        }
        return create_with_grouping();
    }

private:
    /*!
     * \brief Create a figure without grouping.
     *
     * \return Figure.
     */
    [[nodiscard]] figure create_without_grouping() const {
        figure fig;

        auto scatter = fig.add_scatter();
        scatter.mode("lines");
        if (!x_.empty()) {
            scatter.x(*data_.at(x_));
        }
        if (y_.empty()) {
            throw std::runtime_error("y coordinates must be set.");
        }
        scatter.y(*data_.at(y_));

        if (!x_.empty()) {
            fig.layout().xaxis().title().text(x_);
        }
        fig.layout().yaxis().title().text(y_);
        fig.layout().title().text(title_.empty() ? y_ : title_);

        return fig;
    }

    /*!
     * \brief Create a figure with grouping.
     *
     * \return Figure.
     */
    [[nodiscard]] figure create_with_grouping() const {
        figure fig;

        const auto grouping = data_.at(group_)->generate_group();
        const auto& group_values = grouping.first;
        const auto& group_indices = grouping.second;

        std::vector<bool> group_mask(group_indices.size(), false);
        for (std::size_t group_index = 0; group_index < group_values.size();
            ++group_index) {
            for (std::size_t row_index = 0; row_index < group_indices.size();
                ++row_index) {
                group_mask[row_index] =
                    (group_indices[row_index] == group_index);
            }

            const auto group_name =
                fmt::format("{}={}", group_, group_values[group_index]);
            add_trace_for_group(fig, group_mask, group_name);
        }

        if (!x_.empty()) {
            fig.layout().xaxis().title().text(x_);
        }
        fig.layout().yaxis().title().text(y_);
        fig.layout().title().text(title_.empty() ? y_ : title_);

        return fig;
    }

    /*!
     * \brief Add a trace for a group.
     *
     * \param[out] figure Figure to add the trace to.
     * \param[in] group_mask Mask of the values in the group.
     * \param[in] group_name Name of the group.
     */
    void add_trace_for_group(figure& figure,
        const std::vector<bool>& group_mask,
        std::string_view group_name) const {
        auto scatter = figure.add_scatter();
        scatter.mode("lines");
        if (!x_.empty()) {
            scatter.x(filter_data_column(*data_.at(x_), group_mask));
        }
        if (y_.empty()) {
            throw std::runtime_error("y coordinates must be set.");
        }
        scatter.y(filter_data_column(*data_.at(y_), group_mask));
        scatter.name(group_name);
    }

    //! Data.
    const data_table& data_;  // NOLINT(*-ref-data-members)

    //! Column name of x coordinates.
    std::string x_;

    //! Column name of y coordinates.
    std::string y_;

    //! Column name of groups.
    std::string group_;

    //! Title of the figure.
    std::string title_;
};

}  // namespace plotly_plotter::figure_builders
