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
 * \brief Definition of data_column class.
 */
#pragma once

#include <utility>

#include <yyjson.h>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

namespace plotly_plotter {

/*!
 * \brief Class of columns in tables of data.
 *
 * \note Objects of this class should be created from \ref data_table objects.
 * \note Objects of this class doesn't manage the memory of the value,
 * so the objects can be simply copied or moved.
 */
class data_column {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref data_table objects.
     */
    explicit data_column(json_value data) : data_(data) {}

    /*!
     * \brief Append a value to the column.
     *
     * \tparam T Type of the value.
     * \param[in] value Value.
     */
    template <typename T>
    void push_back(T&& value) {
        data_.push_back(std::forward<T>(value));
    }

    /*!
     * \brief Get the JSON data.
     *
     * \return JSON data.
     *
     * \warning This function is defined only for internal use.
     * Future versions may remove this function even not in a major release.
     */
    [[nodiscard]] const json_value& data() const noexcept { return data_; }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Specialization of json_converter class for data_column.
 */
template <>
class json_converter<data_column> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(const data_column& from, json_value& to) {
        if (to.type() == json_value::value_type::array ||
            to.type() == json_value::value_type::object) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }

        if (from.data().type() != json_value::value_type::array) {
            throw std::runtime_error(
                "The type of the column must be an array.");
        }

        yyjson_mut_arr_iter iter =
            yyjson_mut_arr_iter_with(from.data().internal_value());
        yyjson_mut_val* element{};
        while ((element = yyjson_mut_arr_iter_next(&iter)) != nullptr) {
            to.push_back(json_value(element, from.data().internal_document()));
        }
    }
};

/*!
 * \brief Implementation of as_array function for data_column.
 *
 * \param[in] column Column.
 * \return Column.
 */
[[nodiscard]] inline const data_column& as_array(const data_column& column) {
    return column;  // NOLINT
}

}  // namespace plotly_plotter
