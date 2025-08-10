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

#include <cstddef>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "plotly_plotter/array_view.h"
#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_converter_decl.h"
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/to_string.h"
#include "plotly_plotter/utils/calculate_histogram_bin_width.h"

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
     * \param[out] to JSON value to convert to.
     */
    virtual void to_json(json_value to) const = 0;

    /*!
     * \brief Convert the column to a JSON value with a mask.
     *
     * \param[out] to JSON value to convert to.
     * \param[in] mask Mask of the values.
     * Values in this column are added to the JSON array
     * only if the corresponding value in the mask is true.
     */
    virtual void to_json_partial(
        json_value to, const std::vector<bool>& mask) const = 0;

    /*!
     * \brief Generate groups of the values in this column.
     *
     * \return A pair of the values of the groups and the indices of the groups
     * for values.
     *
     * For example if a column has [1, 2, 1, 3, 2], this function returns
     * ([1, 2, 3], [0, 1, 0, 2, 1]).
     */
    [[nodiscard]] virtual std::pair<std::vector<std::string>,
        std::vector<std::size_t>>
    generate_group() const = 0;

    /*!
     * \brief Get the number of values in the column.
     *
     * \return Number of values.
     */
    [[nodiscard]] virtual std::size_t size() const noexcept = 0;

    /*!
     * \brief Get whether the values in the column are numeric.
     *
     * \retval true The values are numeric.
     * \retval false The values are not numeric.
     */
    [[nodiscard]] virtual bool is_numeric() const noexcept = 0;

    /*!
     * \brief Get the range of values in the column.
     *
     * \return Minimum and maximum values in the column.
     *
     * \note This function is only available for columns with numeric values.
     */
    [[nodiscard]] virtual std::pair<double, double> get_range() const = 0;

    /*!
     * \brief Get the range of values in the column in positive numbers.
     *
     * \return Minimum and maximum values in the column.
     *
     * \note This function is only available for columns with numeric values.
     */
    [[nodiscard]] virtual std::pair<double, double> get_positive_range()
        const = 0;

    /*!
     * \brief Calculate the width of bins in histograms.
     *
     * \param[in] method Method to use for calculation.
     * \return Width of bins.
     */
    [[nodiscard]] virtual double calculate_histogram_bin_width(
        utils::histogram_bin_width_method method) = 0;
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

    //! \copydoc data_column_base::to_json_partial
    void to_json_partial(
        json_value to, const std::vector<bool>& mask) const override {
        if (mask.size() != data_.size()) {
            throw std::invalid_argument("Mask size does not match data size.");
        }

        to.set_to_array();
        for (std::size_t i = 0; i < data_.size(); ++i) {
            if (mask[i]) {
                to.push_back(data_[i]);
            }
        }
    }

    //! \copydoc data_column_base::generate_group
    [[nodiscard]] std::pair<std::vector<std::string>, std::vector<std::size_t>>
    generate_group() const override {
        std::unordered_map<value_type, std::size_t> group_to_index;
        std::vector<std::string> groups;
        std::vector<std::size_t> indices;
        indices.reserve(data_.size());
        for (std::size_t i = 0; i < data_.size(); ++i) {
            const auto& value = data_[i];
            auto it = group_to_index.find(value);
            if (it == group_to_index.end()) {
                groups.push_back(to_string(value));
                it = group_to_index.insert({value, groups.size() - 1}).first;
            }
            indices.push_back(it->second);
        }
        return {std::move(groups), std::move(indices)};
    }

    //! \copydoc data_column_base::size
    [[nodiscard]] std::size_t size() const noexcept override {
        return data_.size();
    }

    //! \copydoc data_column_base::is_numeric
    [[nodiscard]] bool is_numeric() const noexcept override {
        return std::is_arithmetic_v<value_type> &&
            std::is_convertible_v<value_type, double>;
    }

    //! \copydoc data_column_base::get_range
    [[nodiscard]] std::pair<double, double> get_range() const override {
        constexpr bool is_supported = std::is_arithmetic_v<value_type> &&
            std::is_convertible_v<value_type, double>;
        if constexpr (!is_supported) {
            throw std::runtime_error(
                "get_range is not supported for this type.");
        } else {
            double min = std::numeric_limits<double>::max();
            double max = std::numeric_limits<double>::min();
            for (const auto& value : data_) {
                const auto value_in_double = static_cast<double>(value);
                min = std::min(min, value_in_double);
                max = std::max(max, value_in_double);
            }
            return {min, max};
        }
    }

    //! \copydoc data_column_base::get_positive_range
    [[nodiscard]] std::pair<double, double> get_positive_range()
        const override {
        constexpr bool is_supported = std::is_arithmetic_v<value_type> &&
            std::is_convertible_v<value_type, double>;
        if constexpr (!is_supported) {
            throw std::runtime_error(
                "get_positive_range is not supported for this type.");
        } else {
            double min = std::numeric_limits<double>::max();
            double max = std::numeric_limits<double>::min();
            for (const auto& value : data_) {
                if (value <= static_cast<value_type>(0)) {
                    continue;
                }
                const auto value_in_double = static_cast<double>(value);
                min = std::min(min, value_in_double);
                max = std::max(max, value_in_double);
            }
            return {min, max};
        }
    }

    //! \copydoc data_column_base::calculate_histogram_bin_width
    [[nodiscard]] double calculate_histogram_bin_width(
        utils::histogram_bin_width_method method) override {
        constexpr bool is_supported = std::is_arithmetic_v<value_type> &&
            std::is_convertible_v<value_type, double>;
        if constexpr (!is_supported) {
            throw std::runtime_error(
                "calculate_histogram_bin_width is not supported for this "
                "type.");
        } else {
            return utils::calculate_histogram_bin_width(data_, method);
        }
    }

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

/*!
 * \brief Class of views of data columns filtered by a mask.
 */
class filtered_data_column_view {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] column Column.
     * \param[in] mask Mask.
     */
    filtered_data_column_view(
        const data_column_base& column, const std::vector<bool>& mask)
        : column_(column), mask_(mask) {}

    /*!
     * \brief Convert the column to a JSON value.
     *
     * \param[out] to JSON value to convert to.
     */
    void to_json(json_value to) const { column_.to_json_partial(to, mask_); }

private:
    //! Column.
    const data_column_base& column_;  // NOLINT(*-ref-data-members)

    //! Mask.
    const std::vector<bool>& mask_;  // NOLINT(*-ref-data-members)
};

/*!
 * \brief Specialization of json_converter class for filtered_data_column_view.
 */
template <>
class json_converter<filtered_data_column_view> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(const filtered_data_column_view& from, json_value& to) {
        from.to_json(to);
    }
};

/*!
 * \brief Create a view of a data column filtered by a mask.
 *
 * \param[in] column Column.
 * \param[in] mask Mask.
 * \return View of the column filtered by the mask.
 */
[[nodiscard]] inline filtered_data_column_view filter_data_column(
    const data_column_base& column, const std::vector<bool>& mask) {
    return filtered_data_column_view(column, mask);
}

/*!
 * \brief Implementation of as_array function for filtered_data_column_view.
 *
 * \param[in] view View.
 * \return View.
 */
[[nodiscard]] inline const filtered_data_column_view& as_array(
    const filtered_data_column_view& view) {
    return view;  // NOLINT
}

}  // namespace plotly_plotter
