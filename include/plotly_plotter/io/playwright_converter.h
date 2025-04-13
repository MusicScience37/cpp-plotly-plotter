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
 * \brief Definition of playwright_converter class.
 */
#pragma once

#include <cstddef>
#include <mutex>
#include <string>

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/io/html_to_pdf_converter_base.h"
#include "plotly_plotter/io/html_to_png_converter_base.h"

namespace plotly_plotter::io {

/*!
 * \brief Converter using Playwright.
 */
class PLOTLY_PLOTTER_EXPORT playwright_converter
    : public html_to_pdf_converter_base,
      public html_to_png_converter_base {
public:
    /*!
     * \brief Get the singleton instance.
     *
     * \return The singleton instance.
     */
    [[nodiscard]] static playwright_converter& get_instance();

    //! \copydoc html_to_pdf_converter_base::is_html_to_pdf_conversion_supported
    [[nodiscard]] bool is_html_to_pdf_conversion_supported() override;

    //! \copydoc html_to_pdf_converter_base::convert_html_to_pdf
    void convert_html_to_pdf(const char* html_file_path,
        const char* pdf_file_path, std::size_t width,
        std::size_t height) override;

    //! \copydoc html_to_png_converter_base::is_html_to_png_conversion_supported
    [[nodiscard]] bool is_html_to_png_conversion_supported() override;

    //! \copydoc html_to_png_converter_base::convert_html_to_png
    void convert_html_to_png(const char* html_file_path,
        const char* png_file_path, std::size_t width,
        std::size_t height) override;

    /*!
     * \brief Get the path of the Python executable.
     *
     * \return The path of the Python executable.
     */
    [[nodiscard]] std::string get_python_path();

    /*!
     * \brief Set the path of the Python executable.
     *
     * \param[in] path The path of the Python executable.
     */
    void set_python_path(std::string path);

    playwright_converter(const playwright_converter&) = delete;
    playwright_converter(playwright_converter&&) = delete;
    playwright_converter& operator=(const playwright_converter&) = delete;
    playwright_converter& operator=(playwright_converter&&) = delete;

    /*!
     * \brief Destructor.
     */
    ~playwright_converter() override;

private:
    /*!
     * \brief Constructor.
     */
    playwright_converter();

    //! Mutex of member variables.
    std::mutex mutex_;

    //! Path to the Python executable.
    std::string python_path_;
};

}  // namespace plotly_plotter::io
