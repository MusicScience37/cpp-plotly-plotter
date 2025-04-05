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
 * \brief Definition of data_table class.
 */
#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "plotly_plotter/data_column.h"
#include "plotly_plotter/details/has_iterator.h"

namespace plotly_plotter {

/*!
 * \brief Class of tables of data.
 */
class data_table {
public:
    /*!
     * \brief Constructor.
     */
    data_table() = default;

    /*!
     * \brief Append a column.
     *
     * \tparam T Type of values in the column.
     * \param[in] name Name of the column.
     * \return Column.
     */
    template <typename T>
    std::shared_ptr<data_column<T>> emplace(std::string name) {
        auto column = std::make_shared<data_column<T>>();
        data_.try_emplace(std::move(name), column);
        return column;
    }

    /*!
     * \brief Append a column.
     *
     * \tparam T Type of values in the column.
     * \param[in] name Name of the column.
     * \param[in] values Values in the column.
     * \return Column.
     */
    template <typename T>
    std::shared_ptr<data_column<T>> emplace(
        std::string name, std::vector<T> values) {
        auto column = std::make_shared<data_column<T>>(std::move(values));
        data_.try_emplace(std::move(name), column);
        return column;
    }

    /*!
     * \brief Append a column.
     *
     * \tparam Container Type of the container of values in the column.
     * \param[in] name Name of the column.
     * \param[in] values Values in the column.
     * \return Column.
     */
    template <typename Container,
        typename = std::enable_if_t<details::has_iterator_v<Container> &&
            !std::is_same_v<std::decay_t<Container>,
                std::vector<typename Container::value_type>>>>
    std::shared_ptr<data_column<typename Container::value_type>> emplace(
        std::string name, Container&& values) {  // NOLINT(*-std-forward)
        std::vector<typename Container::value_type> vec(
            std::begin(values), std::end(values));
        return emplace(std::move(name), std::move(vec));
    }

    /*!
     * \brief Get a column.
     *
     * \param[in] name Name.
     * \return Column.
     */
    [[nodiscard]] std::shared_ptr<data_column_base> at(
        const std::string& name) const {
        auto iter = data_.find(name);
        if (iter == data_.end()) {
            throw std::out_of_range("Column not found: " + name);
        }
        return iter->second;
    }

private:
    //! Data.
    std::unordered_map<std::string, std::shared_ptr<data_column_base>> data_;
};

}  // namespace plotly_plotter
