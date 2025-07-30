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
 * \brief Definition of grid class.
 */
#pragma once

#include <cstddef>
#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

namespace plotly_plotter::layouts {

/*!
 * \brief Class of layout of grid in Plotly.
 *
 * \note Objects of this class should be created from \ref layout objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class grid {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit grid(json_value data) : data_(data) { data_.set_to_object(); }

    /*!
     * \brief Set the number of rows.
     *
     * \param[in] value Value.
     */
    void rows(std::size_t value) { data_["rows"] = value; }

    /*!
     * \brief Set the number of columns.
     *
     * \param[in] value Value.
     */
    void columns(std::size_t value) { data_["columns"] = value; }

    /*!
     * \brief Set the pattern of the grid.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"independent"`: independent
     * - `"coupled"`: coupled (default)
     */
    void pattern(std::string_view value) { data_["pattern"] = value; }

    /*!
     * \brief Set the order of rows.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"top to bottom"`: top to bottom (default)
     * - `"bottom to top"`: bottom to top
     */
    void row_order(std::string_view value) { data_["roworder"] = value; }

    /*!
     * \brief Set the spacing between columns.
     *
     * \param[in] value Value.
     */
    void x_gap(double value) { data_["xgap"] = value; }

    /*!
     * \brief Set the spacing between rows.
     *
     * \param[in] value Value.
     */
    void y_gap(double value) { data_["ygap"] = value; }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter::layouts
