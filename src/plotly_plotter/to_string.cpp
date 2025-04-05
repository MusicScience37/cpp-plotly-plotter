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
 * \brief Implementation of to_string function.
 */
#include "plotly_plotter/to_string.h"

#include <fmt/format.h>

#include "plotly_plotter/details/format_time.h"

namespace plotly_plotter {

std::string to_string_traits<std::timespec>::to_string(
    const std::timespec& value) {
    fmt::memory_buffer buffer;
    details::format_time(value, buffer);
    return std::string(buffer.data(), buffer.size());
}

std::string to_string_traits<std::chrono::system_clock::time_point>::to_string(
    const std::chrono::system_clock::time_point& value) {
    fmt::memory_buffer buffer;
    details::format_time(value, buffer);
    return std::string(buffer.data(), buffer.size());
}

}  // namespace plotly_plotter
