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

#include "plotly_plotter/config.h"
#include "plotly_plotter/json_document.h"
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/styles.h"
#include "plotly_plotter/traces/box.h"
#include "plotly_plotter/traces/heatmap.h"
#include "plotly_plotter/traces/histogram.h"
#include "plotly_plotter/traces/scatter.h"
#include "plotly_plotter/traces/violin.h"

namespace plotly_plotter {

/*!
 * \brief Base class of figures and frames in Plotly.
 */
class figure_frame_base {
public:
    /*!
     * \name Create traces.
     */
    ///@{

    /*!
     * \brief Add a scatter trace to this figure.
     *
     * \return Added scatter trace.
     */
    [[nodiscard]] traces::scatter add_scatter() {
        return traces::scatter(data_.emplace_back());
    }

    /*!
     * \brief Add a scatter trace using WebGL to this figure.
     *
     * \return Added scatter trace.
     */
    [[nodiscard]] traces::scatter_gl add_scatter_gl() {
        return traces::scatter_gl(data_.emplace_back());
    }

    /*!
     * \brief Add a box trace to this figure.
     *
     * \return Added box trace.
     */
    [[nodiscard]] traces::box add_box() {
        return traces::box(data_.emplace_back());
    }

    /*!
     * \brief Add a violin trace to this figure.
     *
     * \return Added violin trace.
     */
    [[nodiscard]] traces::violin add_violin() {
        return traces::violin(data_.emplace_back());
    }

    /*!
     * \brief Add a heatmap trace to this figure.
     *
     * \return Added heatmap trace.
     */
    [[nodiscard]] traces::heatmap add_heatmap() {
        return traces::heatmap(data_.emplace_back());
    }

    /*!
     * \brief Add a histogram trace to this figure.
     *
     * \return Added histogram trace.
     */
    [[nodiscard]] traces::histogram add_histogram() {
        return traces::histogram(data_.emplace_back());
    }

    ///@}

    /*!
     * \brief Access the layout of this figure.
     *
     * \return Layout of this figure.
     */
    [[nodiscard]] plotly_plotter::layouts::layout layout() {
        return plotly_plotter::layouts::layout(layout_);
    }

protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit figure_frame_base(json_value data)
        : data_(data["data"]), layout_(data["layout"]) {
        data_.set_to_array();
        layout_.set_to_object();
    }

    /*!
     * \brief Copy constructor.
     */
    figure_frame_base(const figure_frame_base& /*other*/) = default;

    /*!
     * \brief Move constructor.
     */
    figure_frame_base(figure_frame_base&& /*other*/) = default;

    /*!
     * \brief Copy assignment operator.
     *
     * \return This object.
     */
    figure_frame_base& operator=(const figure_frame_base& /*other*/) = default;

    /*!
     * \brief Move assignment operator.
     *
     * \return This object.
     */
    figure_frame_base& operator=(figure_frame_base&& /*other*/) = default;

    /*!
     * \brief Destructor.
     */
    ~figure_frame_base() = default;

private:
    //! JSON data of traces.
    json_value data_;

    //! JSON data of layout.
    json_value layout_;
};

/*!
 * \brief Class of frames in animation in Plotly.
 */
class animation_frame : public figure_frame_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit animation_frame(json_value data)
        : figure_frame_base(data), json_data_(data) {}

    /*!
     * \brief Set the name of this frame.
     *
     * \param[in] value Value.
     */
    void name(std::string_view value) { json_data_["name"] = value; }

private:
    //! JSON data.
    json_value json_data_;
};

/*!
 * \brief Class of figures in Plotly.
 */
class figure : public figure_frame_base {
public:
    /*!
     * \brief Constructor.
     */
    figure() : figure(json_document()) {}

    /*!
     * \name Configure templates of traces.
     */
    ///@{

    /*!
     * \brief Add a template of scatter traces to this figure.
     *
     * \return Added scatter trace.
     */
    [[nodiscard]] traces::scatter add_scatter_template() {
        return traces::scatter(data_template_.emplace_back());
    }

    /*!
     * \brief Add a template of scatter traces using WebGL to this figure.
     *
     * \return Added scatter trace.
     */
    [[nodiscard]] traces::scatter_gl add_scatter_gl_template() {
        return traces::scatter_gl(data_template_.emplace_back());
    }

    /*!
     * \brief Add a template of box traces to this figure.
     *
     * \return Added box trace.
     */
    [[nodiscard]] traces::box add_box_template() {
        return traces::box(data_template_.emplace_back());
    }

    /*!
     * \brief Add a template of violin traces to this figure.
     *
     * \return Added violin trace.
     */
    [[nodiscard]] traces::violin add_violin_template() {
        return traces::violin(data_template_.emplace_back());
    }

    /*!
     * \brief Add a template of heatmap traces to this figure.
     *
     * \return Added heatmap trace.
     */
    [[nodiscard]] traces::heatmap add_heatmap_template() {
        return traces::heatmap(data_template_.emplace_back());
    }

    /*!
     * \brief Add a template of histogram traces to this figure.
     *
     * \return Added histogram trace.
     */
    [[nodiscard]] traces::histogram add_histogram_template() {
        return traces::histogram(data_template_.emplace_back());
    }

    ///@}

    /*!
     * \brief Access the configuration of this figure.
     *
     * \return Configuration of this figure.
     */
    [[nodiscard]] plotly_plotter::config config() {
        return plotly_plotter::config(config_);
    }

    /*!
     * \brief Access the template of the layout.
     *
     * \return Template of the layout.
     */
    [[nodiscard]] plotly_plotter::layouts::layout layout_template() {
        return plotly_plotter::layouts::layout(layout_template_);
    }

    /*!
     * \brief Add a frame for animation.
     *
     * \return Frame.
     */
    [[nodiscard]] animation_frame add_frame() {
        return animation_frame(document_.root()["frames"].emplace_back());
    }

    /*!
     * \name Helper functions of layout.
     */
    ///@{

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
     * \brief Set the aspect ratio of the axes to be 1:1.
     */
    void square_axis() {
        layout().yaxis().scale_anchor("x");
        layout().yaxis().scale_ratio(1.0);
    }

    /*!
     * \brief Set the title of the x-axis.
     *
     * \param[in] value Value.
     */
    void x_title(std::string_view value) {
        layout().xaxis().title().text(value);
    }

    /*!
     * \brief Set the title of the y-axis.
     *
     * \param[in] value Value.
     */
    void y_title(std::string_view value) {
        layout().yaxis().title().text(value);
    }

    ///@}

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
    /*!
     * \brief Constructor.
     *
     * \param[in] document JSON document.
     */
    explicit figure(json_document document)
        : figure_frame_base(document.root()), document_(std::move(document)) {
        data_.set_to_array();
        layout_.set_to_object();
        config_.set_to_object();
        data_template_.set_to_array();
        layout_template_.set_to_object();
        config().scroll_zoom(true);
        config().responsive(true);
        styles::simple_style(plotly_plotter::layouts::layout(layout_template_));
    }

    //! JSON document of this figure.
    json_document document_;

    //! JSON data of traces.
    json_value data_{document_.root()["data"]};

    //! JSON data of layout.
    json_value layout_{document_.root()["layout"]};

    //! JSON data of configuration.
    json_value config_{document_.root()["config"]};

    //! JSON data of data in templates.
    json_value data_template_{document_.root()["template"]["data"]};

    //! JSON data of layout in templates.
    json_value layout_template_{document_.root()["template"]["layout"]};

    //! Title of the HTML page.
    std::string html_title_{"Untitled Plot"};
};

}  // namespace plotly_plotter
