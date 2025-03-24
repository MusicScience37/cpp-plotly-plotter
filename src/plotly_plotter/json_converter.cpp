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

#include <iterator>

#include <fmt/base.h>
#include <fmt/chrono.h>
#include <fmt/format.h>

namespace plotly_plotter {

void json_converter<std::timespec>::to_json(
    const std::timespec& from, json_value& to) {
    if (to.type() == json_value::value_type::array ||
        to.type() == json_value::value_type::object) {
        throw std::runtime_error(
            "Changing the type of a value from arrays or objects is not "
            "allowed.");
    }
    fmt::memory_buffer buffer;
    fmt::format_to(std::back_inserter(buffer), "{:%Y-%m-%d %H:%M:%S}.{:09d}",
        fmt::localtime(from.tv_sec), from.tv_nsec);
    json_converter<std::string_view>::to_json(
        std::string_view(buffer.data(), buffer.size()), to);
}

}  // namespace plotly_plotter
