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

#include <chrono>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <yyjson.h>

#include "plotly_plotter/json_converter_decl.h"
#include "plotly_plotter/json_value.h"

namespace plotly_plotter {

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
        if (to.type() == json_value::value_type::array ||
            to.type() == json_value::value_type::object) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }
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
        if (to.type() == json_value::value_type::array ||
            to.type() == json_value::value_type::object) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }
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
        if (to.type() == json_value::value_type::array ||
            to.type() == json_value::value_type::object) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }
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
        if (to.type() == json_value::value_type::array ||
            to.type() == json_value::value_type::object) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }
        yyjson_mut_set_real(to.internal_value(), static_cast<double>(from));
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
        if (to.type() == json_value::value_type::array ||
            to.type() == json_value::value_type::object) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }
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
        if (to.type() == json_value::value_type::object) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }
        yyjson_mut_set_arr(to.internal_value());
        yyjson_mut_arr_clear(to.internal_value());
        for (const auto& value : from) {
            to.push_back(value);
        }
    }
};

}  // namespace details

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
    static void to_json(const std::timespec& from, json_value& to) {
        if (to.type() == json_value::value_type::array ||
            to.type() == json_value::value_type::object) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }
        fmt::memory_buffer buffer;
        fmt::format_to(std::back_inserter(buffer),
            "{:%Y-%m-%d %H:%M:%S}.{:09d}", fmt::localtime(from.tv_sec),
            from.tv_nsec);
        json_converter<std::string_view>::to_json(
            std::string_view(buffer.data(), buffer.size()), to);
    }
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
    static void to_json(
        const std::chrono::system_clock::time_point& from, json_value& to) {
        const auto time_point_secs =
            std::chrono::time_point_cast<std::chrono::seconds>(from);
        std::timespec timespec{};
        timespec.tv_sec = std::chrono::system_clock::to_time_t(time_point_secs);
        timespec.tv_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(
            from - time_point_secs)
                               .count();
        json_converter<std::timespec>::to_json(timespec, to);
    }
};

}  // namespace plotly_plotter
