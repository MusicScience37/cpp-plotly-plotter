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
 * \brief Definition of box class.
 */
#pragma once

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/traces/xy_trace_base.h"

namespace plotly_plotter::traces {

/*!
 * \brief Class of box traces in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class box : public xy_trace_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit box(json_value data) : xy_trace_base(data) {
        this->data()["type"] = "box";
    }

    /*!
     * \brief Set whether to show the mean.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `true`: show the mean
     * - `false`: do not show the mean
     * - `"sd"` (using overload with strings): show the mean and standard
     * deviation
     */
    void box_mean(bool value) { this->data()["boxmean"] = value; }

    /*!
     * \brief Set whether to show the mean.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `true` (using overload with bool): show the mean
     * - `false` (using overload with bool): do not show the mean
     * - `"sd"`: show the mean and standard deviation
     */
    void box_mean(std::string_view value) { this->data()["boxmean"] = value; }

    /*!
     * \brief Set whether to show the mean.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `true` (using overload with bool): show the mean
     * - `false` (using overload with bool): do not show the mean
     * - `"sd"`: show the mean and standard deviation
     */
    void box_mean(const char* value) {
        this->box_mean(std::string_view(value));
    }

    /*!
     * \brief Set how points are displayed with the box.
     *
     * \param[in] value Value.
     *
     * Selection:
     *
     * - `"all"`: display all points
     * - `"outliers"`: display only the outliers
     * - `"suspectedoutliers"`: display only the outliers (method to identify
     * outliers is different with `"outliers"`)
     * - `"false"`: do not display any points
     */
    void box_points(std::string_view value) {
        if (value == "false") {
            this->data()["boxpoints"] = false;
        } else {
            this->data()["boxpoints"] = value;
        }
    }
};

}  // namespace plotly_plotter::traces
