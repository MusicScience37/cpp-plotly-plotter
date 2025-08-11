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
 * \brief Definition of bar class.
 */
#pragma once

#include <string_view>
#include <type_traits>

#include "plotly_plotter/details/has_iterator.h"
#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/traces/xy_trace_base.h"

namespace plotly_plotter::traces {

/*!
 * \brief Class to configure markers of bar traces.
 *
 * \note Objects of this class should be created from \ref bar objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class bar_marker {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \note Objects of this class should be created from \ref bar
     * objects.
     * \note Objects of this class doesn't manage the memory of the data,
     * so the objects can be simply copied or moved.
     */
    explicit bar_marker(json_value data) : data_(data) {}

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
 * \brief Class of bar traces in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class bar : public xy_trace_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit bar(json_value data) : xy_trace_base(data) {
        this->data()["type"] = "bar";
    }

    /*!
     * \brief Set the width of the bars.
     *
     * \tparam Container Type of the container of values.
     * \param[in] values Values.
     *
     * \note The container must support `std::begin` and `std::end` functions.
     */
    template <typename Container,
        typename = std::enable_if_t<details::has_iterator_v<Container>>>
    void width(const Container& values) {
        this->data()["width"] = as_array(values);
    }

    /*!
     * \brief Set the width of the bars.
     *
     * \param[in] value Value.
     */
    void width(double value) { this->data()["width"] = value; }

    /*!
     * \brief Set the opacity.
     *
     * \param[in] value Value.
     */
    void opacity(double value) { this->data()["opacity"] = value; }

    /*!
     * \brief Access the configuration of markers.
     *
     * \return Configuration of markers.
     */
    bar_marker marker() { return bar_marker(this->data()["marker"]); }
};

}  // namespace plotly_plotter::traces
