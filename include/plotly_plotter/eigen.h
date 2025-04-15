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
 * \brief Definition of classes to support Eigen library.
 */
#pragma once

#if !__has_include(<Eigen/Core>)
#error "Eigen library is not found. Please install Eigen library."
#endif

#include <Eigen/Core>

#include <yyjson.h>

#include "plotly_plotter/json_converter.h"
#include "plotly_plotter/json_converter_decl.h"
#include "plotly_plotter/json_value.h"

namespace plotly_plotter {

/*!
 * \brief Specialization of json_converter class for Eigen::Matrix.
 *
 * \tparam Scalar Type of values in Eigen::Matrix.
 * \tparam Rows Number of rows in Eigen::Matrix.
 * \tparam Cols Number of columns in Eigen::Matrix.
 * \tparam Options Options of Eigen::Matrix.
 * \tparam MaxRows Maximum number of rows in Eigen::Matrix.
 * \tparam MaxCols Maximum number of columns in Eigen::Matrix.
 */
template <typename Scalar, int Rows, int Cols, int Options, int MaxRows,
    int MaxCols>
class json_converter<
    Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(
        const Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>&
            from,
        json_value& to) {
        details::check_assignment(to);
        if (from.rows() == 1 || from.cols() == 1) {
            // Vectors.
            yyjson_mut_set_arr(to.internal_value());
            yyjson_mut_arr_clear(to.internal_value());
            for (const auto& value : from.reshaped()) {
                to.push_back(value);
            }
        } else {
            // Matrices.
            yyjson_mut_set_arr(to.internal_value());
            yyjson_mut_arr_clear(to.internal_value());
            for (Eigen::Index i = 0; i < from.rows(); ++i) {
                auto row_json = to.emplace_back();
                yyjson_mut_set_arr(row_json.internal_value());
                for (Eigen::Index j = 0; j < from.cols(); ++j) {
                    row_json.push_back(from(i, j));
                }
            }
        }
    }
};

}  // namespace plotly_plotter
