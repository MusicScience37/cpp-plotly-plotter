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
 * \brief Implementation of playwright_converter class.
 */
#include "plotly_plotter/io/playwright_converter.h"

#include <filesystem>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include <fcntl.h>
#include <fmt/format.h>

#include "plotly_plotter/details/file_handle.h"
#include "plotly_plotter/details/templates/generate_pdf_with_playwright.h"
#include "plotly_plotter/details/templates/generate_png_with_playwright.h"
#include "plotly_plotter/io/details/execute_command.h"

namespace plotly_plotter::io {

namespace {

/*!
 * \brief Check if the given path is a valid Python executable with Playwright.
 *
 * \param[in] executable_path Path of the Python executable.
 * \retval true The path is a valid Python executable with Playwright.
 * \retval false The path is not a valid Python executable with Playwright.
 */
[[nodiscard]] bool check_python_executable(const std::string& executable_path) {
    const std::vector<std::string> command{
        executable_path, "-m", "playwright", "--version"};
    return details::check_command_success(command);
}

/*!
 * \brief Find the path of the Python executable with Playwright.
 *
 * \return Path of the Python executable with Playwright.
 */
[[nodiscard]] std::string find_python_path() {
    const std::vector<std::string> possible_paths{"python3", "python"};
    for (const auto& path : possible_paths) {
        if (check_python_executable(path)) {
            return path;
        }
    }
    return possible_paths.front();
}

}  // namespace

playwright_converter& playwright_converter::get_instance() {
    static playwright_converter instance;
    return instance;
}

bool playwright_converter::is_html_to_pdf_conversion_supported() {
    return check_python_executable(get_python_path());
}

void playwright_converter::convert_html_to_pdf(const char* html_file_path,
    const char* pdf_file_path, std::size_t width, std::size_t height) {
    const std::string temp_python_script_path =
        fmt::format("{}.py", pdf_file_path);
    plotly_plotter::details::file_handle temp_python_script_file(
        temp_python_script_path, "w");
    temp_python_script_file.write(
        plotly_plotter::details::templates::generate_pdf_with_playwright);
    temp_python_script_file.close();

    const std::vector<std::string> command{get_python_path(),
        temp_python_script_path, html_file_path, pdf_file_path,
        fmt::to_string(width), fmt::to_string(height)};
    details::execute_command(command);

    std::filesystem::remove(temp_python_script_path);
}

bool playwright_converter::is_html_to_png_conversion_supported() {
    return check_python_executable(get_python_path());
}

void playwright_converter::convert_html_to_png(const char* html_file_path,
    const char* png_file_path, std::size_t width, std::size_t height) {
    const std::string temp_python_script_path =
        fmt::format("{}.py", png_file_path);
    plotly_plotter::details::file_handle temp_python_script_file(
        temp_python_script_path, "w");
    temp_python_script_file.write(
        plotly_plotter::details::templates::generate_png_with_playwright);
    temp_python_script_file.close();

    const std::vector<std::string> command{get_python_path(),
        temp_python_script_path, html_file_path, png_file_path,
        fmt::to_string(width), fmt::to_string(height)};
    details::execute_command(command);

    std::filesystem::remove(temp_python_script_path);
}

std::string playwright_converter::get_python_path() {
    std::unique_lock<std::mutex> lock(mutex_);
    return python_path_;
}

void playwright_converter::set_python_path(std::string path) {
    std::unique_lock<std::mutex> lock(mutex_);
    python_path_ = std::move(path);
}

playwright_converter::~playwright_converter() = default;

playwright_converter::playwright_converter()
    : python_path_(find_python_path()) {}

}  // namespace plotly_plotter::io
