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
 * \brief Definition of violin class.
 */
#pragma once

// IWYU pragma: no_include <string>

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/traces/xy_trace_base.h"

namespace plotly_plotter::traces {

/*!
 * \brief Class of configuration of boxes in violin traces.
 *
 * \note Objects of this class should be created from \ref violin objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class violin_box {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref violin objects.
     */
    explicit violin_box(json_value data) : data_(data) {
        data_.set_to_object();
    }

    /*!
     * \brief Set whether to show the box.
     *
     * \param[in] value Value.
     */
    void visible(bool value) { data_["visible"] = value; }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class of configuration of mean lines in violin traces.
 *
 * \note Objects of this class should be created from \ref violin objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class violin_mean_line {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref violin objects.
     */
    explicit violin_mean_line(json_value data) : data_(data) {
        data_.set_to_object();
    }

    /*!
     * \brief Set whether to show the mean line.
     *
     * \param[in] value Value.
     */
    void visible(bool value) { data_["visible"] = value; }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class of violin traces in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class violin : public xy_trace_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit violin(json_value data) : xy_trace_base(data) {
        this->data()["type"] = "violin";
    }

    /*!
     * \brief Access the configuration of boxes.
     *
     * \return Configuration of boxes.
     */
    [[nodiscard]] violin_box box() {  // NOLINT(*-member-function-const)
        // This function modifies the internal state.
        return violin_box(data()["box"]);
    }

    /*!
     * \brief Access the configuration of mean lines.
     *
     * \return Configuration of mean lines.
     */
    [[nodiscard]] violin_mean_line
    mean_line() {  // NOLINT(*-member-function-const)
                   // This function modifies the internal state.
        return violin_mean_line(data()["meanline"]);
    }

    /*!
     * \brief Set the mode of points.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"all"`: show all points
     * - `"outliers"`: show only outliers
     * - `"suspectedoutliers"`: display only the outliers (method to identify
     * outliers is different with `"outliers"`)
     * - `"false"`: do not display any points
     */
    void points(std::string_view value) {
        if (value == "false") {
            data()["points"] = false;
        } else {
            data()["points"] = value;
        }
    }

    /*!
     * \brief Set the color.
     *
     * \param[in] value Value.
     */
    void color(std::string_view value) {  // NOLINT(*-member-function-const)
        // This function modifies the internal state.
        this->data()["marker"]["color"] = value;
        this->data()["outliercolor"] = value;
        this->data()["line"]["color"] = value;
        this->data()["box"]["line"]["color"] = value;
        this->data()["meanline"]["color"] = value;
    }

    /*!
     * \brief Set the group for offset.
     *
     * \param[in] value Value.
     */
    void offset_group(std::string_view value) {
        this->data()["offsetgroup"] = value;
    }
};

}  // namespace plotly_plotter::traces
