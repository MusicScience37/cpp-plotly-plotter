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
 * \brief Definition of heatmap class.
 */
#pragma once

// IWYU pragma: no_include <string>

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/traces/xy_trace_base.h"

namespace plotly_plotter::traces {

/*!
 * \brief Class of heatmap traces.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class heatmap : public xy_trace_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit heatmap(json_value data) : xy_trace_base(data) {
        this->data()["type"] = "heatmap";
    }

    /*!
     * \brief Set the z coordinates.
     *
     * \tparam Container Type of the container of values.
     * \param[in] values Values.
     *
     * Input can be either a 1D or 2D array.
     * When 1D array is given, x and y must have the same length.
     * When 2D array is given, the outer dimension (rows) must have the same
     * length as y, and the inner dimension (columns) must have the same length
     * as x.
     * When a matrix in Eigen library is given, rows are interpreted as the
     * outer dimension regardless of the storage order in the matrix.
     */
    template <typename Container>
    void z(const Container& values) {
        this->data()["z"] = values;
    }

    /*!
     * \brief Set the color axis.
     *
     * \param[in] value Value.
     */
    void color_axis(std::string_view value) {
        this->data()["coloraxis"] = value;
    }

    /*!
     * \brief Set smoothing of the z coordinates.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"fast"`
     * - `"best"`
     * - `"false"`: do not smooth
     */
    void z_smooth(std::string_view value) {
        if (value == "false") {
            this->data()["zsmooth"] = false;
        } else {
            this->data()["zsmooth"] = value;
        }
    }
};

}  // namespace plotly_plotter::traces
