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
 * \brief Definition of histogram class.
 */
#pragma once

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/traces/xy_trace_base.h"

namespace plotly_plotter::traces {

/*!
 * \brief Class to configure markers of histogram traces.
 *
 * \note Objects of this class should be created from \ref histogram objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class histogram_marker {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \note Objects of this class should be created from \ref histogram
     * objects.
     * \note Objects of this class doesn't manage the memory of the data,
     * so the objects can be simply copied or moved.
     */
    explicit histogram_marker(json_value data) : data_(data) {}

    /*!
     * \brief Set the color.
     *
     * \param[in] value Value.
     */
    void color(std::string_view value) {  // NOLINT(*-member-function-const)
        data_["color"] = value;
    }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class to configure bins of histogram traces.
 */
class histogram_bins {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit histogram_bins(json_value data) : data_(data) {}

    /*!
     * \brief Set the number of bins.
     *
     * \param[in] value Value.
     */
    void size(double value) { data_["size"] = value; }

    /*!
     * \brief Set the start of bins.
     *
     * \param[in] value Value.
     */
    void start(double value) { data_["start"] = value; }

    /*!
     * \brief Set the end of bins.
     *
     * \param[in] value Value.
     */
    void end(double value) { data_["end"] = value; }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class of histogram traces in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class histogram : public xy_trace_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit histogram(json_value data) : xy_trace_base(data) {
        this->data()["type"] = "histogram";
    }

    /*!
     * \brief Access the configuration of markers.
     *
     * \return Configuration.
     */
    [[nodiscard]] histogram_marker marker() {
        return histogram_marker(this->data()["marker"]);
    }

    /*!
     * \brief Access the configuration of bins of x-axis.
     *
     * \return Configuration.
     */
    [[nodiscard]] histogram_bins x_bins() {
        return histogram_bins(this->data()["xbins"]);
    }

    /*!
     * \brief Access the configuration of bins of y-axis.
     *
     * \return Configuration.
     */
    [[nodiscard]] histogram_bins y_bins() {
        return histogram_bins(this->data()["ybins"]);
    }

    /*!
     * \brief Set the opacity.
     *
     * \param[in] value Value.
     */
    void opacity(double value) { this->data()["opacity"] = value; }
};

}  // namespace plotly_plotter::traces
