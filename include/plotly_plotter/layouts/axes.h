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
 * \brief Definition of classes of axes.
 */
#pragma once

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/layouts/title_base.h"

namespace plotly_plotter::layouts {

/*!
 * \brief Class of titles of axes in Plotly.
 *
 * \note Objects of this class should be created from \ref xaxis, \ref yaxis
 * objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class axis_title : public title_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref xaxis, \ref yaxis objects.
     */
    explicit axis_title(json_value data) : title_base(data) {}
};

/*!
 * \brief Base class of axes in Plotly.
 */
class axis_base {
public:
    /*!
     * \brief Access the title of the x-axis.
     *
     * \return Title of the x-axis.
     */
    [[nodiscard]] axis_title title() { return axis_title(data_["title"]); }

    /*!
     * \brief Set the type of the axis.
     *
     * \param[in] value Value.
     *
     * Value can be one of the following:
     *
     * - `"-"` (auto)
     * - `"linear"`
     * - `"log"`
     * - `"date"`
     * - `"category"`
     * - `"multicategory"`
     */
    void type(std::string_view value) { data_["type"] = value; }

    /*!
     * \brief Set the range of the axis.
     *
     * \tparam Min Type of the minimum value.
     * \tparam Max Type of the maximum value.
     * \param[in] min Minimum value.
     * \param[in] max Maximum value.
     *
     * \note If type is set to `"log"`, values must be the log of the actual
     * values.
     * \note To left either minimum or maximum unset, use `nullptr`.
     */
    template <typename Min, typename Max>
    void range(Min min, Max max) {
        data_["range"].push_back(min);
        data_["range"].push_back(max);
    }

    /*!
     * \brief Set the way to compress the axis.
     *
     * \param[in] value Value.
     */
    void constrain(std::string_view value) { data_["constrain"] = value; }

    /*!
     * \brief Set the another axis to which the range is linked.
     *
     * \param[in] value Value.
     */
    void matches(std::string_view value) { data_["matches"] = value; }

    /*!
     * \brief Set whether to show the line of the axis.
     *
     * \param[in] value Value.
     */
    void show_line(bool value) { data_["showline"] = value; }

    /*!
     * \brief Set the color of the line of the axis.
     *
     * \param[in] value Value.
     */
    void line_color(std::string_view value) { data_["linecolor"] = value; }

    /*!
     * \brief Set the color of the lines of the grid.
     *
     * \param[in] value Value.
     */
    void grid_color(std::string_view value) { data_["gridcolor"] = value; }

    /*!
     * \brief Set the color of the line at zero.
     *
     * \param[in] value Value.
     */
    void zero_line_color(std::string_view value) {
        data_["zerolinecolor"] = value;
    }

    /*!
     * \brief Set the place of the tics.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"outside"`: outside.
     * - `"inside"`: inside.
     * - `""`: no ticks.
     */
    void ticks(std::string_view value) { data_["ticks"] = value; }

    /*!
     * \brief Set whether to show axes on the opposite side.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"true"`: show axes on the opposite side.
     * - `"false"`: do not show axes on the opposite side.
     * - `"ticks"`: show ticks on the opposite side.
     * - `"all"`: show axes on all the subplots.
     * - `"allticks"`: show ticks on all the subplots.
     */
    void mirror(std::string_view value) {
        if (value == "true") {
            data_["mirror"] = true;
        } else if (value == "false") {
            data_["mirror"] = false;
        } else {
            data_["mirror"] = value;
        }
    }

    /*!
     * \brief Set whether to show labels of ticks.
     *
     * \param[in] value Value.
     */
    void show_tick_labels(bool value) { data_["showticklabels"] = value; }

    /*!
     * \brief Set the axis according to which this axis is scaled.
     *
     * \param[in] value Value.
     */
    void scale_anchor(std::string_view value) { data_["scaleanchor"] = value; }

    /*!
     * \brief Set the ratio of the axis to the axis given in scale_anchor().
     *
     * \param[in] value Value.
     */
    void scale_ratio(double value) { data_["scaleratio"] = value; }

    /*!
     * \brief Set the width of the line.
     *
     * \param[in] value Value.
     */
    void line_width(double value) { data_["linewidth"] = value; }

protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit axis_base(json_value data) : data_(data) { data_.set_to_object(); }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class of layout of x-axis in Plotly.
 *
 * \note Objects of this class should be created from \ref layout objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class xaxis : public axis_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref layout objects.
     */
    explicit xaxis(json_value data) : axis_base(data) {}
};

/*!
 * \brief Class of layout of y-axis in Plotly.
 *
 * \note Objects of this class should be created from \ref layout objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class yaxis : public axis_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref layout objects.
     */
    explicit yaxis(json_value data) : axis_base(data) {}
};

}  // namespace plotly_plotter::layouts
