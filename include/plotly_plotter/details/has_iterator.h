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
 * \brief Definition of has_iterator class.
 */
#pragma once

#include <iterator>
#include <type_traits>
#include <utility>

namespace plotly_plotter::details {

/*!
 * \brief Helper class to check if a type has iterators.
 */
struct has_iterator_impl {
    /*!
     * \brief Check if a type has iterators.
     *
     * \tparam T Type to check.
     * \return Object of std::true_type if the type has iterators,
     * std::false_type otherwise.
     */
    template <typename T>
    static auto test(int) -> decltype(std::begin(std::declval<T>()),
        std::end(std::declval<T>()), std::true_type());

    /*!
     * \brief Check if a type has iterators.
     *
     * \tparam T Type to check.
     * \return Object of std::true_type if the type has iterators,
     * std::false_type otherwise.
     */
    template <typename>
    static auto test(...) -> std::false_type;
};

/*!
 * \brief Class to check if a type has iterators.
 *
 * \tparam T Type to check.
 *
 * This class inherits from std::true_type if the type has iterators,
 * std::false_type otherwise.
 */
template <typename T>
struct has_iterator : decltype(has_iterator_impl::test<T>(0)) {};

/*!
 * \brief Check if a type has iterators.
 *
 * \tparam T Type to check.
 */
template <typename T>
constexpr bool has_iterator_v = has_iterator<T>::value;

}  // namespace plotly_plotter::details
