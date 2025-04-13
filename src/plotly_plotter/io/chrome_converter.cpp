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
#include <stdexcept>
#include <string>
#include <vector>

#include <fmt/format.h>

#include "plotly_plotter/details/execute_command.h"
#include "plotly_plotter/details/get_chrome_path.h"

#ifdef linux
#include <stdlib.h>  // NOLINT
#endif

namespace plotly_plotter::io {

chrome_converter& chrome_converter::get_instance() {
    static chrome_converter instance;
    return instance;
}

#ifdef linux

bool chrome_converter::is_html_to_pdf_conversion_supported() {
    std::vector<std::string> command{
        static_cast<std::string>(get_chrome_path()), "--version"};

    const auto [status, command_output] =
        plotly_plotter::details::execute_command(command, true);

    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

void chrome_converter::convert_html_to_pdf(const char* html_file_path,
    const char* pdf_file_path, std::size_t width, std::size_t height) {
    std::vector<std::string> command{
        static_cast<std::string>(get_chrome_path()), "--headless",
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

    constexpr bool capture_logs = true;
    const auto [status, command_output] =
        plotly_plotter::details::execute_command(command, capture_logs);

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        if (WIFSIGNALED(status)) {
            throw std::runtime_error(
                fmt::format("Failed to generate PDF with signal {}.{}",
                    WTERMSIG(status), command_output));
        }
        throw std::runtime_error(
            fmt::format("Failed to generate PDF with status {}.{}",
                WEXITSTATUS(status), command_output));
    }
}

chrome_converter::chrome_converter()
    : chrome_path_(plotly_plotter::details::get_chrome_path()) {}

#else

bool chrome_converter::is_html_to_pdf_conversion_supported() { return false; }

void chrome_converter::convert_html_to_pdf(const char* html_file_path,
    const char* pdf_file_path, std::size_t width, std::size_t height) {
    (void)html_file_path;
    (void)pdf_file_path;
    (void)width;
    (void)height;
    throw std::runtime_error("PDF is not supported for this platform.");
}

chrome_converter::chrome_converter() = default;

#endif

std::string chrome_converter::get_chrome_path() {
    std::unique_lock<std::mutex> lock(mutex_);
    return chrome_path_;
}

void chrome_converter::set_chrome_path(std::string path) {
    std::unique_lock<std::mutex> lock(mutex_);
    chrome_path_ = std::move(path);
}

chrome_converter::~chrome_converter() = default;

}  // namespace plotly_plotter::io
