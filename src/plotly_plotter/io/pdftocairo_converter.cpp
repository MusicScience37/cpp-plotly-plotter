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
 * \brief Implementation of pdftocairo_converter class.
 */
#include "plotly_plotter/io/pdftocairo_converter.h"

#include <filesystem>  // IWYU pragma: keep
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include "plotly_plotter/details/config.h"
#include "plotly_plotter/io/details/execute_command.h"

namespace plotly_plotter::io {

namespace {
/*!
 * \brief Check if the given path is a valid pdftocairo executable.
 *
 * \param[in] executable_path Path of the pdftocairo executable.
 * \retval true The path is a valid pdftocairo executable.
 * \retval false The path is not a valid pdftocairo executable.
 */
[[nodiscard]] bool check_pdftocairo_executable(
    const std::string& executable_path) {
#if PLOTLY_PLOTTER_USE_WIN_SUBPROCESS
    // Currently not supported.
    (void)executable_path;
    return false;
#else
    const std::vector<std::string> command{executable_path, "-v"};
    return details::check_command_success(command);
#endif
}

}  // namespace

pdftocairo_converter& pdftocairo_converter::get_instance() {
    static pdftocairo_converter instance;
    return instance;
}

bool pdftocairo_converter::is_pdf_to_svg_conversion_supported() {
    return check_pdftocairo_executable(get_pdftocairo_path());
}

void pdftocairo_converter::convert_pdf_to_svg(
    const char* pdf_file_path, const char* svg_file_path) {
    std::vector<std::string> command{
        get_pdftocairo_path(), pdf_file_path, "-svg", svg_file_path};
    details::execute_command(command);
}

std::string pdftocairo_converter::get_pdftocairo_path() {
    std::unique_lock<std::mutex> lock(mutex_);
    return pdftocairo_path_;
}

void pdftocairo_converter::set_pdftocairo_path(const std::string& path) {
    std::unique_lock<std::mutex> lock(mutex_);
    pdftocairo_path_ = path;
}

pdftocairo_converter::~pdftocairo_converter() = default;

pdftocairo_converter::pdftocairo_converter() : pdftocairo_path_("pdftocairo") {}

}  // namespace plotly_plotter::io
