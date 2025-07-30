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
 * \brief Definition of annotation class.
 */
#pragma once

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

namespace plotly_plotter::layouts {

/*!
 * \brief Class of annotations in Plotly.
 *
 * \note Objects of this class should be created from \ref layout objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class annotation {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit annotation(json_value data) : data_(data) {
        data_.set_to_object();
    }

    /*!
     * \brief Set the alignment of the text.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"left"`: left
     * - `"center"`: center
     * - `"right"`: right
     */
    void align(std::string_view value) { data_["align"] = value; }

    /*!
     * \brief Set whether to show the arrow.
     *
     * \param[in] value Value.
     */
    void show_arrow(bool value) { data_["showarrow"] = value; }

    /*!
     * \brief Set the text of the annotation.
     *
     * \param[in] value Value.
     */
    void text(std::string_view value) { data_["text"] = value; }

    /*!
     * \brief Set the x-coordinate of the annotation.
     *
     * \param[in] value Value.
     *
     * \note Meaning of this value depends on the value given to x_ref()
     * function.
     */
    void x(double value) { data_["x"] = value; }

    /*!
     * \brief Set the y-coordinate of the annotation.
     *
     * \param[in] value Value.
     *
     * \note Meaning of this value depends on the value given to y_ref()
     * function.
     */
    void y(double value) { data_["y"] = value; }

    /*!
     * \brief Set the reference of the x-coordinate.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"paper"`: paper
     * - `"x"`, `"x2"`, `"x3"`, ...: x-axis (value of the axis)
     * - `"x domain"`, `"x2 domain"`, `"x3 domain"`, ...: x-axis (rate of the
     * position relative to the axis)
     */
    void x_ref(std::string_view value) { data_["xref"] = value; }

    /*!
     * \brief Set the reference of the y-coordinate.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"paper"`: paper
     * - `"y"`, `"y2"`, `"y3"`, ...: y-axis (value of the axis)
     * - `"y domain"`, `"y2 domain"`, `"y3 domain"`, ...: y-axis (rate of the
     * position relative to the axis)
     */
    void y_ref(std::string_view value) { data_["yref"] = value; }

    /*!
     * \brief Set the shift of the x-coordinate in pixels.
     *
     * \param[in] value Value.
     */
    void x_shift(double value) { data_["xshift"] = value; }

    /*!
     * \brief Set the shift of the y-coordinate in pixels.
     *
     * \param[in] value Value.
     */
    void y_shift(double value) { data_["yshift"] = value; }

    /*!
     * \brief Set the angle of the text.
     *
     * \param[in] value Value.
     *
     * \note The value is in degrees.
     */
    void text_angle(double value) { data_["textangle"] = value; }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter::layouts
