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
 * \brief Definition of scatter class.
 */
#pragma once

#include <string_view>
#include <type_traits>

#include "plotly_plotter/array_view.h"
#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/traces/xy_trace_base.h"

namespace plotly_plotter::traces {

/*!
 * \brief Class to configure error bars in scatter traces.
 *
 * \note Objects of this class should be created from \ref scatter objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class scatter_error {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref scatter objects.
     */
    explicit scatter_error(json_value data) : data_(data) {}

    /*!
     * \brief Set the type of error bars.
     *
     * \param[in] value Value.
     *
     * Selection:
     *
     * - `"percent"`
     * - `"constant"`
     * - `"sqrt"`
     * - `"data"` (use data passed to array() function and optional
     * array_minus() function are used.)
     */
    void type(std::string_view value) { data_["type"] = value; }

    /*!
     * \brief Set whether the error bars are symmetric.
     *
     * \param[in] value Value.
     */
    void symmetric(bool value) { data_["symmetric"] = value; }

    /*!
     * \brief Set whether the error bars are visible.
     *
     * \param[in] value Value.
     */
    void visible(bool value) { data_["visible"] = value; }

    /*!
     * \brief Set the data of the error bars as an array of values.
     *
     * \tparam Container Type of the container of values.
     * \param[in] values Values.
     */
    template <typename Container>
    void array(const Container& values) {
        data_["array"] = as_array(values);
    }

    /*!
     * \brief Set the data of the error bars as an array of values.
     *
     * \tparam Container Type of the container of values.
     * \param[in] values Values.
     */
    template <typename Container>
    void array_minus(const Container& values) {
        data_["arrayminus"] = as_array(values);
    }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class to configure the line of scatter traces.
 *
 * \note Objects of this class should be created from \ref scatter objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class scatter_line {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref scatter objects.
     */
    explicit scatter_line(json_value data) : data_(data) {}

    /*!
     * \brief Set the dash style of the line.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"solid"`
     * - `"dot"`
     * - `"dash"`
     * - `"longdash"`
     * - `"dashdot"`
     * - `"longdashdot"`
     */
    void dash(std::string_view value) { data_["dash"] = value; }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class to configure the marker of scatter traces.
 *
 * \note Objects of this class should be created from \ref scatter objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class scatter_marker {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref scatter objects.
     */
    explicit scatter_marker(json_value data) : data_(data) {}

    /*!
     * \brief Set the color of the marker.
     *
     * \param[in] value Value.
     */
    void color(std::string_view value) { data_["color"] = value; }

    /*!
     * \brief Set the color of the marker by an array of values.
     *
     * \tparam Container Type of the container of values.
     * \param[in] value Value.
     */
    template <typename Container,
        typename = std::enable_if_t<
            !std::is_convertible_v<Container, std::string_view>>>
    void color(const Container& value) {
        data_["color"] = as_array(value);
    }

    /*!
     * \brief Set the color axis.
     *
     * \param[in] value Value.
     */
    void color_axis(std::string_view value) { data_["coloraxis"] = value; }

    /*!
     * \brief Set the size of the marker.
     *
     * \param[in] value Value.
     */
    void size(double value) { data_["size"] = value; }

    /*!
     * \brief Set the size of the marker by an array of values.
     *
     * \tparam Container Type of the container of values.
     * \param[in] value Value.
     */
    template <typename Container,
        typename = std::enable_if_t<!std::is_convertible_v<Container, double>>>
    void size(const Container& value) {
        data_["size"] = as_array(value);
    }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Base class of scatter traces.
 */
class scatter_base : public xy_trace_base {
public:
    /*!
     * \brief Access the configuration of error bars in x direction.
     *
     * \return Configuration.
     */
    [[nodiscard]] scatter_error error_x() {  // NOLINT(*-member-function-const)
        // This function modifies the internal state.
        return scatter_error(this->data()["error_x"]);
    }

    /*!
     * \brief Access the configuration of error bars in y direction.
     *
     * \return Configuration.
     */
    [[nodiscard]] scatter_error error_y() {  // NOLINT(*-member-function-const)
        // This function modifies the internal state.
        return scatter_error(this->data()["error_y"]);
    }

    /*!
     * \brief Set the mode of the trace.
     *
     * \param[in] value Value.
     *
     * Selection:
     *
     * - `lines`
     * - `markers`
     * - `text`
     * - Combinations of the above joined with `+`, for example `lines+markers`.
     * - `none`
     */
    void mode(std::string_view value) {  // NOLINT(*-member-function-const)
        // This function modifies the internal state.
        this->data()["mode"] = value;
    }

    /*!
     * \brief Access the configuration of the line.
     *
     * \return Configuration.
     */
    [[nodiscard]] scatter_line line() {  // NOLINT(*-member-function-const)
        // This function modifies the internal state.
        return scatter_line(this->data()["line"]);
    }

    /*!
     * \brief Access the configuration of the marker.
     *
     * \return Configuration.
     */
    [[nodiscard]] scatter_marker marker() {  // NOLINT(*-member-function-const)
        // This function modifies the internal state.
        return scatter_marker(this->data()["marker"]);
    }

    /*!
     * \brief Set the color.
     *
     * \param[in] value Value.
     */
    void color(std::string_view value) {  // NOLINT(*-member-function-const)
        // This function modifies the internal state.
        marker().color(value);
        this->data()["line"]["color"] = value;
    }

protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit scatter_base(json_value data) : xy_trace_base(data) {}
};

/*!
 * \brief Class of scatter traces in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class scatter : public scatter_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit scatter(json_value data) : scatter_base(data) {
        this->data()["type"] = "scatter";
    }
};

/*!
 * \brief Class of scatter traces using WebGL in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 *
 * \warning Mode "text" doesn't work in WebGL.
 */
class scatter_gl : public scatter_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit scatter_gl(json_value data) : scatter_base(data) {
        this->data()["type"] = "scattergl";
    }
};

}  // namespace plotly_plotter::traces
