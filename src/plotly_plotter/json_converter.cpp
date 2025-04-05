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
 * \brief Implementation of specializations of json_converter class.
 */
#include "plotly_plotter/json_converter.h"

#include <fmt/format.h>

#include "plotly_plotter/details/format_time.h"

namespace plotly_plotter {

void json_converter<std::timespec>::to_json(
    const std::timespec& from, json_value& to) {
    details::check_assignment(to);
    fmt::memory_buffer buffer;
    details::format_time(from, buffer);
    json_converter<std::string_view>::to_json(
        std::string_view(buffer.data(), buffer.size()), to);
}

void json_converter<std::chrono::system_clock::time_point>::to_json(
    const std::chrono::system_clock::time_point& from, json_value& to) {
    details::check_assignment(to);
    fmt::memory_buffer buffer;
    details::format_time(from, buffer);
    json_converter<std::string_view>::to_json(
        std::string_view(buffer.data(), buffer.size()), to);
}

}  // namespace plotly_plotter
