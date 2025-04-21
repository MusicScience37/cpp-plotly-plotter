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
 * \brief Definition of pdftocairo_converter class.
 */
#pragma once

#include <cstddef>
#include <mutex>
#include <string>

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/io/pdf_to_svg_converter_base.h"

namespace plotly_plotter::io {

/*!
 * \brief Converter using pdftocairo command.
 */
class PLOTLY_PLOTTER_EXPORT pdftocairo_converter
    : public pdf_to_svg_converter_base {
public:
    /*!
     * \brief Get the singleton instance.
     *
     * \return The singleton instance.
     */
    [[nodiscard]] static pdftocairo_converter& get_instance();

    //! \copydoc pdf_to_svg_converter_base::is_pdf_to_svg_conversion_supported
    [[nodiscard]] bool is_pdf_to_svg_conversion_supported() override;

    //! \copydoc pdf_to_svg_converter_base::convert_pdf_to_svg
    void convert_pdf_to_svg(
        const char* pdf_file_path, const char* svg_file_path) override;

    /*!
     * \brief Get the path to the pdftocairo command.
     *
     * \return The path to the pdftocairo command.
     */
    [[nodiscard]] std::string get_pdftocairo_path();

    /*!
     * \brief Set the path to the pdftocairo command.
     *
     * \param[in] path The path to the pdftocairo command.
     */
    void set_pdftocairo_path(const std::string& path);

    pdftocairo_converter(const pdftocairo_converter&) = delete;
    pdftocairo_converter(pdftocairo_converter&&) = delete;
    pdftocairo_converter& operator=(const pdftocairo_converter&) = delete;
    pdftocairo_converter& operator=(pdftocairo_converter&&) = delete;

    /*!
     * \brief Destructor.
     */
    ~pdftocairo_converter() override;

private:
    /*!
     * \brief Constructor.
     */
    pdftocairo_converter();

    //! Mutex of member variables.
    std::mutex mutex_;

    //! Path to the pdftocairo command.
    std::string pdftocairo_path_;
};

}  // namespace plotly_plotter::io
