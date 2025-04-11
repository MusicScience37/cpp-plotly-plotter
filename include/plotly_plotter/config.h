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
 * \brief Definition of config class.
 */
#pragma once

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

namespace plotly_plotter {

/*!
 * \brief Class of configuration of Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class config {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit config(json_value data) : data_(data) {}

    /*!
     * \brief Set the scroll and zoom option.
     *
     * \param[in] value Value.
     */
    void scroll_zoom(bool value) { data_["scrollZoom"] = value; }

    /*!
     * \brief Set whether to permit editing the figure.
     *
     * \param[in] value Value.
     */
    void editable(bool value) { data_["editable"] = value; }

    /*!
     * \brief Set whether to show a static plot.
     *
     * \param[in] value Value.
     */
    void static_plot(bool value) { data_["staticPlot"] = value; }

    /*!
     * \brief Set whether to show the mode bar.
     *
     * \param[in] value Value.
     */
    void display_mode_bar(bool value) { data_["displayModeBar"] = value; }

    /*!
     * \brief Set whether to set the plot to be responsive.
     *
     * \param[in] value Value.
     */
    void responsive(bool value) { data_["responsive"] = value; }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter
