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
 * \brief Definition of specializations of json_converter class.
 */
#pragma once

#include <array>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include <yyjson.h>

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/json_converter_decl.h"
#include "plotly_plotter/json_value.h"

namespace plotly_plotter {

namespace details {

/*!
 * \brief Check if the assignment is valid.
 *
 * \param[in] target JSON value to check.
 */
inline void check_assignment(const json_value& target) {
    if (target.type() == json_value::value_type::array ||
        target.type() == json_value::value_type::object) {
        throw std::runtime_error(
            "Changing the type of a value from arrays or objects is not "
            "allowed.");
    }
}

}  // namespace details

/*!
 * \brief Specialization of json_converter class for bool.
 */
template <>
class json_converter<bool> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(bool from, json_value& to) {
        details::check_assignment(to);
        yyjson_mut_set_bool(to.internal_value(), from);
    }
};

/*!
 * \brief Specialization of json_converter class for unsigned integer types.
 *
 * \tparam T Type to convert to JSON values.
 */
template <typename T>
class json_converter<T,
    std::enable_if_t<std::is_integral_v<T> && std::is_unsigned_v<T>>> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(T from, json_value& to) {
        details::check_assignment(to);
        yyjson_mut_set_uint(
            to.internal_value(), static_cast<std::uint64_t>(from));
    }
};

/*!
 * \brief Specialization of json_converter class for signed integer types.
 *
 * \tparam T Type to convert to JSON values.
 */
template <typename T>
class json_converter<T,
    std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>>> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(T from, json_value& to) {
        details::check_assignment(to);
        yyjson_mut_set_sint(
            to.internal_value(), static_cast<std::int64_t>(from));
    }
};

/*!
 * \brief Specialization of json_converter class for floating-point types.
 *
 * \tparam T Type to convert to JSON values.
 */
template <typename T>
class json_converter<T, std::enable_if_t<std::is_floating_point_v<T>>> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(T from, json_value& to) {
        details::check_assignment(to);
        if (std::isfinite(from)) {
            yyjson_mut_set_real(to.internal_value(), static_cast<double>(from));
        } else {
            yyjson_mut_set_null(to.internal_value());
        }
    }
};

/*!
 * \brief Specialization of json_converter class for std::string.
 *
 * \tparam T Type to convert to JSON values.
 */
template <typename T>
class json_converter<T,
    std::enable_if_t<std::is_same_v<T, std::string> ||
        std::is_same_v<T, std::string_view>>> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(const T& from, json_value& to) {
        details::check_assignment(to);
        yyjson_mut_set_strn(to.internal_value(),
            unsafe_yyjson_mut_strncpy(
                to.internal_document(), from.data(), from.size()),
            from.size());
    }
};

/*!
 * \brief Specialization of json_converter class for const char*.
 */
template <>
class json_converter<const char*> : public json_converter<std::string_view> {};

/*!
 * \brief Specialization of json_converter class for char*.
 */
template <>
class json_converter<char*> : public json_converter<std::string_view> {};

/*!
 * \brief Specialization of json_converter class for const char arrays.
 */
template <std::size_t Size>
class json_converter<const char[Size]>
    : public json_converter<std::string_view> {};

/*!
 * \brief Specialization of json_converter class for char arrays.
 */
template <std::size_t Size>
class json_converter<char[Size]> : public json_converter<std::string_view> {};

namespace details {

/*!
 * \brief Implementation of json_converter class for array types.
 *
 * \tparam T Type to convert to JSON values.
 */
template <typename T>
class array_json_converter {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(const T& from, json_value& to) {
        details::check_assignment(to);
        yyjson_mut_set_arr(to.internal_value());
        yyjson_mut_arr_clear(to.internal_value());
        for (const auto& value : from) {
            to.push_back(value);
        }
    }
};

}  // namespace details

/*!
 * \brief Specialization of json_converter class for std::vector.
 *
 * \tparam T Type of values in std::vector.
 * \tparam Allocator Type of allocator for std::vector.
 */
template <typename T, typename Allocator>
class json_converter<std::vector<T, Allocator>>
    : public details::array_json_converter<std::vector<T, Allocator>> {};

/*!
 * \brief Specialization of json_converter class for std::array.
 *
 * \tparam T Type of values in std::array.
 * \tparam Size Size of std::array.
 */
template <typename T, std::size_t Size>
class json_converter<std::array<T, Size>>
    : public details::array_json_converter<std::array<T, Size>> {};

/*!
 * \brief Specialization of json_converter class for std::timespec.
 */
template <>
class json_converter<std::timespec> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    PLOTLY_PLOTTER_EXPORT static void to_json(
        const std::timespec& from, json_value& to);
};

/*!
 * \brief Specialization of json_converter class for
 * std::chrono::system_clock::time_point.
 */
template <>
class json_converter<std::chrono::system_clock::time_point> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    PLOTLY_PLOTTER_EXPORT static void to_json(
        const std::chrono::system_clock::time_point& from, json_value& to);
};

/*!
 * \brief Specialization of json_converter class for std::nullptr_t.
 */
template <>
class json_converter<std::nullptr_t> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[out] to JSON value to convert to.
     */
    static void to_json(std::nullptr_t, json_value& to) {
        details::check_assignment(to);
        yyjson_mut_set_null(to.internal_value());
    }
};

/*!
 * \brief Specialization of json_converter class for std::pair.
 *
 * \tparam T1 Type of first element in std::pair.
 * \tparam T2 Type of second element in std::pair.
 */
template <typename T1, typename T2>
class json_converter<std::pair<T1, T2>> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(const std::pair<T1, T2>& from, json_value& to) {
        details::check_assignment(to);
        yyjson_mut_set_arr(to.internal_value());
        yyjson_mut_arr_clear(to.internal_value());
        to.push_back(from.first);
        to.push_back(from.second);
    }
};

/*!
 * \brief Specialization of json_converter class for std::tuple.
 *
 * \tparam Types Type of elements in std::tuple.
 */
template <typename... Types>
class json_converter<std::tuple<Types...>> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(const std::tuple<Types...>& from, json_value& to) {
        details::check_assignment(to);
        yyjson_mut_set_arr(to.internal_value());
        yyjson_mut_arr_clear(to.internal_value());
        to_json_helper<0>(from, to);
    }

private:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \tparam Index Index of the element in std::tuple.
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    template <std::size_t Index>
    static void to_json_helper(
        const std::tuple<Types...>& from, json_value& to) {
        if constexpr (Index < sizeof...(Types)) {
            to.push_back(std::get<Index>(from));
            to_json_helper<Index + 1>(from, to);
        }
    }
};

}  // namespace plotly_plotter
