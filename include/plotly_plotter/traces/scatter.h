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

#include "plotly_plotter/array_view.h"
#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

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

namespace details {

/*!
 * \brief Base class of scatter traces.
 */
class scatter_base {
public:
    /*!
     * \brief Set the trace name used in legends.
     *
     * \param[in] value Value.
     */
    void name(std::string_view value) { data_["name"] = value; }

    /*!
     * \brief Set the x coordinates.
     *
     * \tparam Container Type of the container of values.
     * \param[in] values Values.
     *
     * \note The container must support `std::begin` and `std::end` functions.
     */
    template <typename Container>
    void x(const Container& values) {
        data_["x"] = as_array(values);
    }

    /*!
     * \brief Set the y coordinates.
     *
     * \tparam Container Type of the container of values.
     * \param[in] values Values.
     *
     * \note The container must support `std::begin` and `std::end` functions.
     */
    template <typename Container>
    void y(const Container& values) {
        data_["y"] = as_array(values);
    }

    /*!
     * \brief Access the configuration of error bars in x direction.
     *
     * \return Configuration.
     */
    [[nodiscard]] scatter_error error_x() {
        return scatter_error(data_["error_x"]);
    }

    /*!
     * \brief Access the configuration of error bars in y direction.
     *
     * \return Configuration.
     */
    [[nodiscard]] scatter_error error_y() {
        return scatter_error(data_["error_y"]);
    }

    /*!
     * \brief Set the text for each point.
     *
     * \tparam Container Type of the container of texts.
     * \param[in] values Values.
     *
     * \note The container must support `std::begin` and `std::end` functions.
     */
    template <typename Container>
    void text(const Container& values) {
        data_["text"] = as_array(values);
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
    void mode(std::string_view value) { data_["mode"] = value; }

    /*!
     * \brief Set the template string used for hover texts.
     *
     * \param[in] value Value.
     *
     * \note x, y, and text values can be inserted using `%{x}`, `%{y}`, and
     * `%{text}` respectively.
     * For details, see
     * [hovertemplate](https://plotly.com/javascript/hover-text-and-formatting/#hovertemplate)
     * in Plotly.js document.
     */
    void hover_template(std::string_view value) {
        data_["hovertemplate"] = value;
    }

    /*!
     * \brief Get the JSON data for this trace.
     *
     * \return JSON data.
     *
     * \warning This function is for advanced users who want to customize the
     * trace data directly.
     */
    [[nodiscard]] json_value data() const noexcept { return data_; }

protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit scatter_base(json_value data) : data_(data) {}

private:
    //! JSON data.
    json_value data_;
};

}  // namespace details

/*!
 * \brief Class of scatter traces in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class scatter : public details::scatter_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit scatter(json_value data) : details::scatter_base(data) {
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
class scatter_gl : public details::scatter_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit scatter_gl(json_value data) : details::scatter_base(data) {
        this->data()["type"] = "scattergl";
    }
};

}  // namespace plotly_plotter::traces
