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
 * \brief Definition of chrome_converter class.
 */
#pragma once

#include <mutex>
#include <string>

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/io/html_to_pdf_converter_base.h"

namespace plotly_plotter::io {

/*!
 * \brief Converter using Google Chrome.
 */
class PLOTLY_PLOTTER_EXPORT chrome_converter
    : public html_to_pdf_converter_base {
public:
    /*!
     * \brief Get the singleton instance.
     *
     * \return The singleton instance.
     */
    [[nodiscard]] static chrome_converter& get_instance();

    //! \copydoc html_to_pdf_converter_base::is_html_to_pdf_conversion_supported
    [[nodiscard]] bool is_html_to_pdf_conversion_supported() override;

    //! \copydoc html_to_pdf_converter_base::convert_html_to_pdf
    void convert_html_to_pdf(const char* html_file_path,
        const char* pdf_file_path, std::size_t width,
        std::size_t height) override;

    /*!
     * \brief Get the path of the Chrome executable.
     *
     * \return The path of the Chrome executable.
     */
    [[nodiscard]] std::string get_chrome_path();

    /*!
     * \brief Set the path of the Chrome executable.
     *
     * \param[in] path The path of the Chrome executable.
     */
    void set_chrome_path(std::string path);

    chrome_converter(const chrome_converter&) = delete;
    chrome_converter(chrome_converter&&) = delete;
    chrome_converter& operator=(const chrome_converter&) = delete;
    chrome_converter& operator=(chrome_converter&&) = delete;

    /*!
     * \brief Destructor.
     */
    ~chrome_converter() override;

private:
    /*!
     * \brief Constructor.
     */
    chrome_converter();

    //! Mutex of member variables.
    std::mutex mutex_;

    //! Path to the Chrome executable.
    std::string chrome_path_;
};

}  // namespace plotly_plotter::io
