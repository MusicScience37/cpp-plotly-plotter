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
 * \brief Class of scatter traces in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class scatter {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit scatter(json_value data) : data_(data) {
        data_["type"] = "scatter";
    }

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
     * \brief Get the JSON data for this trace.
     *
     * \return JSON data.
     *
     * \warning This function is for advanced users who want to customize the
     * trace data directly.
     */
    [[nodiscard]] json_value data() const noexcept { return data_; }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter::traces
