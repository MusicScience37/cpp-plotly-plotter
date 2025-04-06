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
 * \brief Definition of line function.
 */
#pragma once

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure_builders/scatter.h"

namespace plotly_plotter::figure_builders {

/*!
 * \brief Create a \ref scatter object to create a line plot.
 *
 * \param[in] data Data.
 * \return \ref scatter object.
 */
[[nodiscard]] inline scatter line(const data_table& data) {
    return scatter(data).mode("lines");
}

}  // namespace plotly_plotter::figure_builders
