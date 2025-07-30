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
 * \brief Definition of classes of color bars.
 */
#pragma once

#include <string_view>
#include <utility>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/layouts/title_base.h"

namespace plotly_plotter::layouts {

/*!
 * \brief Class of title of color bar in Plotly.
 *
 * \note Objects of this class should be created from \ref color_bar objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class color_bar_title : public title_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref color_bar objects.
     */
    explicit color_bar_title(json_value data) : title_base(data) {}
};

/*!
 * \brief Class of layout of color bar in Plotly.
 *
 * \note Objects of this class should be created from \ref color_axis objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class color_bar {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit color_bar(json_value data) : data_(data) { data_.set_to_object(); }

    /*!
     * \brief Access the title of the color bar.
     *
     * \return Title of the color bar.
     */
    [[nodiscard]] color_bar_title title() {
        return color_bar_title(data_["title"]);
    }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class of layout of color axis in Plotly.
 *
 * \note Objects of this class should be created from \ref layout objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class color_axis {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit color_axis(json_value data) : data_(data) {
        data_.set_to_object();
    }

    /*!
     * \brief Set the maximum value of the color axis.
     *
     * \param[in] value Value.
     */
    void c_max(double value) { data_["cmax"] = value; }

    /*!
     * \brief Set the minimum value of the color axis.
     *
     * \param[in] value Value.
     */
    void c_min(double value) { data_["cmin"] = value; }

    /*!
     * \brief Access the layout of the color bar.
     *
     * \return Layout of the color bar.
     */
    [[nodiscard]] plotly_plotter::layouts::color_bar color_bar() {
        return plotly_plotter::layouts::color_bar(data_["colorbar"]);
    }

    /*!
     * \brief Set whether to show the color bar.
     *
     * \param[in] value Value.
     */
    void show_scale(bool value) { data_["showscale"] = value; }

    /*!
     * \brief Set the color scale.
     *
     * \tparam T Type of the value.
     * \param[in] value Value.
     *
     * Input can be one of the following:
     * - A string of the name of the color scale.
     *   Selection:
     *   Blackbody,Bluered,Blues,Cividis,Earth,Electric,Greens,Greys,
     *   Hot,Jet,Picnic,Portland,Rainbow,RdBu,Reds,Viridis,YlGnBu,YlOrRd
     * - A list of mapping of normalized value (from 0 to 1) to color.
     *   For example,
     *   `{{0.0, "#FF0000"}, {1.0, "#0000FF"}}`.
     */
    template <typename T>
    void color_scale(T&& value) {
        data_["colorscale"] = std::forward<T>(value);
    }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter::layouts
