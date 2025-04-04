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
 * \brief Definition of layout class.
 */
#pragma once

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

namespace plotly_plotter {

/*!
 * \brief Base class of titles in Plotly.
 */
class title_base {
public:
    /*!
     * \brief Set the text of the title.
     *
     * \param[in] value Value.
     */
    void text(std::string_view value) { data_["text"] = value; }

protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit title_base(json_value data) : data_(data) {
        data_.set_to_object();
    }

private:
    //! JSON data.
    json_value data_;
};

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
 * \brief Class of titles of figures in Plotly.
 *
 * \note Objects of this class should be created from \ref layout objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class figure_title : public title_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref layout objects.
     */
    explicit figure_title(json_value data) : title_base(data) {}
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

/*!
 * \brief Class of layout in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class layout {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit layout(json_value data) : data_(data) {}

    /*!
     * \brief Access the x-axis.
     *
     * \return X-axis.
     */
    [[nodiscard]] plotly_plotter::xaxis xaxis() {
        return plotly_plotter::xaxis(data_["xaxis"]);
    }

    /*!
     * \brief Access the y-axis.
     *
     * \return Y-axis.
     */
    [[nodiscard]] plotly_plotter::yaxis yaxis() {
        return plotly_plotter::yaxis(data_["yaxis"]);
    }

    /*!
     * \brief Access the title of the figure.
     *
     * \return Title of the figure.
     */
    [[nodiscard]] figure_title title() { return figure_title(data_["title"]); }

    /*!
     * \brief Set the mode of showing box traces.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"group"`: group traces without overlaying
     * - `"overlay"`: overlay traces
     */
    void box_mode(std::string_view value) { data_["boxmode"] = value; }

    /*!
     * \brief Set the mode of showing violin traces.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"group"`: group traces without overlaying
     * - `"overlay"`: overlay traces
     */
    void violin_mode(std::string_view value) { data_["violinmode"] = value; }

    /*!
     * \brief Set whether to show the legend.
     *
     * \param[in] value Value.
     */
    void show_legend(bool value) { data_["showlegend"] = value; }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter
