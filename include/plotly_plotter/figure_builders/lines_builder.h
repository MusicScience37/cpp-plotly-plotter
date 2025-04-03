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
 * \brief Definition of lines_builder class.
 */
#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

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
class lines_builder {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     *
     * \note This class hold the reference of the data.
     * So, the data must be valid until this object is destructed.
     */
    explicit lines_builder(const data_table& data) : data_(data) {}

    /*!
     * \brief Set the column name of x coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    lines_builder& x(std::string value) {
        x_ = std::move(value);
        return *this;
    }

    /*!
     * \brief Set the column name of y coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    lines_builder& y(std::string value) {
        y_ = std::move(value);
        return *this;
    }

    /*!
     * \brief Set the title of the figure.
     *
     * \param[in] value Value.
     * \return This object.
     */
    lines_builder& title(std::string value) {
        title_ = std::move(value);
        return *this;
    }

    /*!
     * \brief Create a figure.
     *
     * \return Figure.
     */
    [[nodiscard]] figure build() const {
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

private:
    //! Data.
    const data_table& data_;  // NOLINT(*-ref-data-members)

    //! Column name of x coordinates.
    std::string x_;

    //! Column name of y coordinates.
    std::string y_;

    //! Title of the figure.
    std::string title_;
};

}  // namespace plotly_plotter::figure_builders
