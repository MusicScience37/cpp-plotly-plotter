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
 * \brief Implementation of chrome_converter class.
 */
#include "plotly_plotter/io/chrome_converter.h"

#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include "plotly_plotter/io/details/execute_command.h"

namespace plotly_plotter::io {

namespace {

/*!
 * \brief Check if the given path is a valid Chrome executable.
 *
 * \param[in] executable_path Path of the Chrome executable.
 * \retval true The path is a valid Chrome executable.
 * \retval false The path is not a valid Chrome executable.
 */
[[nodiscard]] bool check_chrome_executable(const std::string& executable_path) {
    const std::vector<std::string> command{executable_path, "--version"};
    return details::check_command_success(command);
}

/*!
 * \brief Find the path of the Chrome executable.
 *
 * \return Path of the Chrome executable.
 */
[[nodiscard]] std::string find_chrome_path() {
    const std::vector<std::string> possible_paths{
        "google-chrome", "google-chrome-stable", "chrome"};
    for (const auto& path : possible_paths) {
        if (check_chrome_executable(path)) {
            return path;
        }
    }
    return possible_paths.front();
}

}  // namespace

chrome_converter& chrome_converter::get_instance() {
    static chrome_converter instance;
    return instance;
}

bool chrome_converter::is_html_to_pdf_conversion_supported() {
    return check_chrome_executable(get_chrome_path());
}

void chrome_converter::convert_html_to_pdf(const char* html_file_path,
    const char* pdf_file_path, std::size_t width, std::size_t height) {
    std::vector<std::string> command{get_chrome_path(), "--headless",
        fmt::format("--print-to-pdf={}", pdf_file_path),
        fmt::format("--window-size={},{}", width, height),
        "--no-pdf-header-footer",
        // --no-sandbox is required for running chrome as root user.
        "--no-sandbox",
        // GPU can not be used in ordinary Docker containers.
        "--disable-gpu", "--enable-unsafe-swiftshader",
        // Disable crash reporting.
        "--disable-breakpad",
        // Disable dialogs.
        "--no-first-run", "--no-default-browser-check",
        // Prevent crash because of shared memory.
        "--disable-dev-shm-usage",
        // Disable component updates.
        "--disable-component-update", html_file_path};
    details::execute_command(command);
}

bool chrome_converter::is_html_to_png_conversion_supported() {
    return check_chrome_executable(get_chrome_path());
}

void chrome_converter::convert_html_to_png(const char* html_file_path,
    const char* png_file_path, std::size_t width, std::size_t height) {
    std::vector<std::string> command{get_chrome_path(), "--headless",
        fmt::format("--screenshot={}", png_file_path),
        fmt::format("--window-size={},{}", width, height),
        // --no-sandbox is required for running chrome as root user.
        "--no-sandbox",
        // GPU can not be used in ordinary Docker containers.
        "--disable-gpu", "--enable-unsafe-swiftshader",
        // Disable crash reporting.
        "--disable-breakpad",
        // Disable dialogs.
        "--no-first-run", "--no-default-browser-check",
        // Prevent crash because of shared memory.
        "--disable-dev-shm-usage",
        // Disable component updates.
        "--disable-component-update", html_file_path};
    details::execute_command(command);
}

std::string chrome_converter::get_chrome_path() {
    std::unique_lock<std::mutex> lock(mutex_);
    return chrome_path_;
}

void chrome_converter::set_chrome_path(std::string path) {
    std::unique_lock<std::mutex> lock(mutex_);
    chrome_path_ = std::move(path);
}

chrome_converter::~chrome_converter() = default;

chrome_converter::chrome_converter() : chrome_path_(find_chrome_path()) {}

}  // namespace plotly_plotter::io
