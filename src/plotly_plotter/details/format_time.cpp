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
 * \brief Implementation of format_time function.
 */
#include "plotly_plotter/details/format_time.h"

#include <iterator>

#include <fmt/base.h>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <time.h>  // NOLINT: required for C functions.

namespace plotly_plotter::details {

void format_time(const std::timespec& value, fmt::memory_buffer& buffer) {
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &value.tv_sec);
#else
    (void)localtime_r(&value.tv_sec, &tm);
#endif

    fmt::format_to(std::back_inserter(buffer), "{:%Y-%m-%d %H:%M:%S}.{:09d}",
        tm, value.tv_nsec);
}

void format_time(const std::chrono::system_clock::time_point& value,
    fmt::memory_buffer& buffer) {
    const auto time_point_secs =
        std::chrono::time_point_cast<std::chrono::seconds>(value);
    std::timespec timespec{};
    timespec.tv_sec = std::chrono::system_clock::to_time_t(time_point_secs);
    timespec.tv_nsec = static_cast<long>(  // NOLINT
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            value - time_point_secs)
            .count());
    format_time(timespec, buffer);
}

}  // namespace plotly_plotter::details
