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
 * \brief Definition of figure class.
 */
#pragma once

#include <string>
#include <string_view>

#include "plotly_plotter/json_document.h"
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/scatter.h"

namespace plotly_plotter {

/*!
 * \brief Class of figures in Plotly.
 */
class figure {
public:
    /*!
     * \brief Constructor.
     */
    figure() {
        data_.set_to_array();
        layout_.set_to_object();
    }

    /*!
     * \brief Add a scatter trace to this figure.
     *
     * \return Added scatter trace.
     */
    [[nodiscard]] traces::scatter add_scatter() {
        return traces::scatter(data_.emplace_back());
    }

    /*!
     * \brief Access the layout of this figure.
     *
     * \return Layout of this figure.
     */
    [[nodiscard]] plotly_plotter::layout layout() {
        return plotly_plotter::layout(layout_);
    }

    /*!
     * \brief Set the title of this figure.
     *
     * \param[in] value Value.
     *
     * \note This function sets both the title in the plot and the title of the
     * HTML page.
     */
    void title(std::string_view value) {
        html_title(value);
        layout().title().text(value);
    }

    /*!
     * \brief Set the title of the HTML page.
     *
     * \param[in] value Value.
     */
    void html_title(std::string_view value) {
        html_title_ = static_cast<std::string>(value);
    }

    /*!
     * \brief Get the JSON document of this figure.
     *
     * \return JSON document.
     *
     * \warning This function is for internal use and for advanced users who
     * want to customize the trace data directly.
     */
    [[nodiscard]] json_document& document() noexcept { return document_; }

    /*!
     * \brief Get the JSON document of this figure.
     *
     * \return JSON document.
     *
     * \warning This function is for internal use and for advanced users who
     * want to customize the trace data directly.
     */
    [[nodiscard]] const json_document& document() const noexcept {
        return document_;
    }

    /*!
     * \brief Get the title in HTML.
     *
     * \return Title in HTML.
     */
    [[nodiscard]] const std::string& html_title() const noexcept {
        return html_title_;
    }

private:
    //! JSON document of this figure.
    json_document document_;

    //! JSON data of traces.
    json_value data_{document_.root()["data"]};

    //! JSON data of layout.
    json_value layout_{document_.root()["layout"]};

    //! Title of the HTML page.
    std::string html_title_{"Untitled Plot"};
};

}  // namespace plotly_plotter
