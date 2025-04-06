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
 * \brief Definition of array_view class.
 */
#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

#include "plotly_plotter/details/has_iterator.h"
#include "plotly_plotter/json_converter.h"
#include "plotly_plotter/json_converter_decl.h"

namespace plotly_plotter {

/*!
 * \brief Class of views of arrays.
 *
 * \tparam Iterator Type of iterators.
 *
 * \note Objects of this class can be used to assign to a json_value object.
 */
template <typename Iterator>
class array_view {
public:
    //! Type of iterators.
    using iterator = Iterator;

    //! Type of values.
    using value_type = typename std::iterator_traits<iterator>::value_type;

    //! Type of references.
    using reference = typename std::iterator_traits<iterator>::reference;

    //! Type of pointers.
    using pointer = typename std::iterator_traits<iterator>::pointer;

    //! Type of differences between iterators.
    using difference_type =
        typename std::iterator_traits<iterator>::difference_type;

    /*!
     * \brief Constructor.
     *
     * \param[in] begin Iterator to the beginning of the array.
     * \param[in] end Iterator to the end of the array.
     */
    array_view(iterator begin, iterator end) : begin_(begin), end_(end) {}

    /*!
     * \brief Constructor.
     *
     * \param[in] container Container to create a view.
     *
     * \note The container must support `std::begin` and `std::end` functions.
     */
    template <typename T,
        typename = std::enable_if_t<!std::is_same_v<T, array_view>>>
    // NOLINTNEXTLINE(*-explicit-constructor,*-explicit-conversions)
    array_view(const T& container)
        : begin_(std::begin(container)), end_(std::end(container)) {}

    /*!
     * \brief Get an iterator to the beginning of the array.
     *
     * \return Iterator to the beginning of the array.
     */
    [[nodiscard]] iterator begin() const { return begin_; }

    /*!
     * \brief Get an iterator to the end of the array.
     *
     * \return Iterator to the end of the array.
     */
    [[nodiscard]] iterator end() const { return end_; }

private:
    //! Iterator to the beginning of the array.
    iterator begin_;

    //! Iterator to the end of the array.
    iterator end_;
};

/*!
 * \brief Function to create an array_view from a container.
 *
 * \tparam T Type of the container.
 * \param container Container to create a view.
 * \return Created array_view.
 *
 * \note The container must support `std::begin` and `std::end` functions.
 * \note The return value can be usable to assign to a json_value object.
 */
template <typename T>
[[nodiscard]] auto as_array(const T& container)
    -> std::enable_if_t<details::has_iterator_v<T>,
        array_view<decltype(std::begin(container))>> {
    return array_view<decltype(std::begin(container))>(container);
}

/*!
 * \brief Specialization of json_converter class for array_view.
 *
 * \tparam Iterator Type of iterators.
 */
template <typename Iterator>
class json_converter<array_view<Iterator>>
    : public details::array_json_converter<array_view<Iterator>> {};

}  // namespace plotly_plotter
