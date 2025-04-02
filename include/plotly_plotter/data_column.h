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
#include <vector>

#include "plotly_plotter/array_view.h"
#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

namespace plotly_plotter {

/*!
 * \brief Base class of columns in tables of data.
 */
class data_column_base {
public:
    /*!
     * \brief Constructor.
     */
    data_column_base() = default;

    /*!
     * \brief Destructor.
     */
    virtual ~data_column_base() = default;

    data_column_base(const data_column_base&) = delete;
    data_column_base(data_column_base&&) = delete;
    data_column_base& operator=(const data_column_base&) = delete;
    data_column_base& operator=(data_column_base&&) = delete;

    /*!
     * \brief Convert the column to a JSON value.
     *
     * \param[in] to JSON value to convert to.
     */
    virtual void to_json(json_value to) const = 0;
};

/*!
 * \brief Class of columns in tables of data.
 *
 * \tparam T Type of the value.
 *
 * \note Objects of this class should be created from \ref data_table objects.
 * \note Objects of this class doesn't manage the memory of the value,
 * so the objects can be simply copied or moved.
 */
template <typename T>
class data_column : public data_column_base {
public:
    //! Type of values.
    using value_type = T;

    /*!
     * \brief Constructor.
     */
    data_column() = default;

    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     */
    explicit data_column(std::vector<T> data) : data_(std::move(data)) {}

    /*!
     * \brief Constructor.
     *
     * \tparam Iterator Type of iterators.
     * \param[in] begin Iterator to the first element.
     * \param[in] end Iterator to the past-the-last element.
     */
    template <typename Iterator>
    data_column(Iterator begin, Iterator end) : data_(begin, end) {}

    /*!
     * \brief Append a value to the column.
     *
     * \tparam U Type of the value.
     * \param[in] value Value.
     */
    template <typename U>
    void push_back(U&& value) {
        data_.push_back(std::forward<U>(value));
    }

    //! \copydoc data_column_base::to_json
    void to_json(json_value to) const override { to = as_array(data_); }

private:
    //! Data.
    std::vector<value_type> data_;
};

/*!
 * \brief Specialization of json_converter class for data_column_base.
 */
template <>
class json_converter<data_column_base> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(const data_column_base& from, json_value& to) {
        from.to_json(to);
    }
};

/*!
 * \brief Implementation of as_array function for data_column_base.
 *
 * \param[in] column Column.
 * \return Column.
 */
[[nodiscard]] inline const data_column_base& as_array(
    const data_column_base& column) {
    return column;  // NOLINT
}

}  // namespace plotly_plotter
