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
 * \brief Definition of format_time function.
 */
#pragma once

#include <chrono>
#include <ctime>

#include <fmt/format.h>

#include "plotly_plotter/details/plotly_plotter_export.h"

namespace plotly_plotter::details {

/*!
 * \brief Format a time value.
 *
 * \param[in] value Value to format.
 * \param[out] buffer Buffer to store the formatted string.
 */
PLOTLY_PLOTTER_EXPORT void format_time(
    const std::timespec& value, fmt::memory_buffer& buffer);

/*!
 * \brief Format a time value.
 *
 * \param[in] value Value to format.
 * \param[out] buffer Buffer to store the formatted string.
 */
PLOTLY_PLOTTER_EXPORT void format_time(
    const std::chrono::system_clock::time_point& value,
    fmt::memory_buffer& buffer);

}  // namespace plotly_plotter::details
