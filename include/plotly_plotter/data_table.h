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
 * \brief Definition of data_table class.
 */
#pragma once

#include <string_view>
#include <utility>

#include "plotly_plotter/array_view.h"
#include "plotly_plotter/data_column.h"
#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_document.h"
#include "plotly_plotter/json_value.h"

namespace plotly_plotter {

/*!
 * \brief Class of tables of data.
 */
class data_table {
public:
    /*!
     * \brief Constructor.
     */
    data_table() = default;

    /*!
     * \brief Append a column.
     *
     * \tparam T Type of values in the column.
     * \param[in] name Name of the column.
     * \param[in] values Values in the column.
     */
    template <typename T>
    void emplace(std::string_view name, T&& values) {
        data_[name] = as_array(std::forward<T>(values));
    }

    /*!
     * \brief Append a column or return the existing one if exists.
     *
     * \param[in] name Name of the column.
     * \return Column.
     */
    [[nodiscard]] data_column operator[](std::string_view name) {
        auto value = data_[name];
        value.set_to_array();
        return data_column(value);
    }

    /*!
     * \brief Get a column.
     *
     * \param[in] name Name.
     * \return Column.
     */
    [[nodiscard]] data_column at(std::string_view name) const {
        return data_column(data_.at(name));
    }

    /*!
     * \brief Get the JSON document.
     *
     * \return JSON document.
     *
     * \warning This function is defined only for internal use.
     * Future versions may remove this function even not in a major release.
     */
    [[nodiscard]] const json_document& data() const noexcept {
        return document_;
    }

private:
    //! JSON document.
    json_document document_;

    //! JSON data.
    json_value data_{document_.root()};
};

}  // namespace plotly_plotter
