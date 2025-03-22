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
 * \brief Declaration of json_converter class.
 */
#pragma once

namespace plotly_plotter {

/*!
 * \brief Class to convert various types to JSON values.
 *
 * \tparam T Type to convert to JSON values.
 * \tparam Enabler Argument used for SFINAE.
 *
 * Implementations of this class should have the following members:
 *
 * ```cpp
 * // Convert an object to a JSON value.
 * static void to_json(const T& from, json_value& to);
 * ```
 */
template <typename T, typename Enabler = void>
class json_converter;

}  // namespace plotly_plotter
