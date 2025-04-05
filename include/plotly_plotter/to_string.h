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
 * \brief Definition of to_string function.
 */
#pragma once

#include <chrono>
#include <ctime>
#include <string>

#include <fmt/format.h>

#include "plotly_plotter/details/plotly_plotter_export.h"

namespace plotly_plotter {

/*!
 * \brief Class to convert a value to a string.
 *
 * \tparam T Type of the value.
 */
template <typename T>
class to_string_traits {
public:
    /*!
     * \brief Convert a value to a string.
     *
     * \param[in] value Value.
     * \return String representation of the value.
     */
    static std::string to_string(const T& value) {
        return fmt::to_string(value);
    }
};

/*!
 * \brief Specialization of to_string_traits class for std::timespec.
 */
template <>
class to_string_traits<std::timespec> {
public:
    /*!
     * \brief Convert a value to a string.
     *
     * \param[in] value Value.
     * \return String representation of the value.
     */
    PLOTLY_PLOTTER_EXPORT static std::string to_string(
        const std::timespec& value);
};

/*!
 * \brief Specialization of to_string_traits class for
 * std::chrono::system_clock::time_point.
 */
template <>
class to_string_traits<std::chrono::system_clock::time_point> {
public:
    /*!
     * \brief Convert a value to a string.
     *
     * \param[in] value Value.
     * \return String representation of the value.
     */
    PLOTLY_PLOTTER_EXPORT static std::string to_string(
        const std::chrono::system_clock::time_point& value);
};

/*!
 * \brief Convert a value to a string.
 *
 * \tparam T Type of the value.
 * \param[in] value Value.
 * \return String representation of the value.
 */
template <typename T>
inline std::string to_string(const T& value) {
    return to_string_traits<T>::to_string(value);
}

}  // namespace plotly_plotter
