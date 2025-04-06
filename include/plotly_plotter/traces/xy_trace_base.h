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
 * \brief Definition of xy_trace_base class.
 */
#pragma once

#include <string_view>

#include "plotly_plotter/array_view.h"
#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

namespace plotly_plotter::traces {

/*!
 * \brief Base class of traces with x and y coordinates.
 */
class xy_trace_base {
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
     * \brief Set the x-axis to which this trace is linked.
     *
     * \param[in] value Value.
     */
    void xaxis(std::string_view value) { data_["xaxis"] = value; }

    /*!
     * \brief Set the y-axis to which this trace is linked.
     *
     * \param[in] value Value.
     */
    void yaxis(std::string_view value) { data_["yaxis"] = value; }

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
     * \brief Set the legend group.
     *
     * \param[in] value Value.
     */
    void legend_group(std::string_view value) { data_["legendgroup"] = value; }

    /*!
     * \brief Set whether to show in the legend.
     *
     * \param[in] value Value.
     */
    void show_legend(bool value) { data_["showlegend"] = value; }

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
     */
    explicit xy_trace_base(json_value data) : data_(data) {}

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter::traces
