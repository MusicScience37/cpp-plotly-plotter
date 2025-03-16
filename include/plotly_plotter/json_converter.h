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
        yyjson_mut_set_bool(to.internal_value(), from);
    }
};

}  // namespace plotly_plotter
