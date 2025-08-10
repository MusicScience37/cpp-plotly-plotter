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
 * \brief Definition of layout class.
 */
#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/layouts/animation.h"
#include "plotly_plotter/layouts/annotation.h"
#include "plotly_plotter/layouts/axes.h"
#include "plotly_plotter/layouts/color_axis.h"
#include "plotly_plotter/layouts/figure_title.h"
#include "plotly_plotter/layouts/grid.h"
#include "plotly_plotter/layouts/legend.h"

namespace plotly_plotter::layouts {

/*!
 * \brief Class of layout in Plotly.
 *
 * \note Objects of this class should be created from \ref figure objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class layout {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref figure objects.
     */
    explicit layout(json_value data) : data_(data) {}

    /*!
     * \brief Access the x-axis.
     *
     * \return X-axis.
     */
    [[nodiscard]] plotly_plotter::layouts::xaxis xaxis() {
        return plotly_plotter::layouts::xaxis(data_["xaxis"]);
    }

    /*!
     * \brief Access the x-axis.
     *
     * \param[in] index Index of the x-axis.
     * \return X-axis.
     */
    [[nodiscard]] plotly_plotter::layouts::xaxis xaxis(std::size_t index) {
        if (index == 0) {
            throw std::out_of_range("Index of x-axis must be greater than 0");
        }
        if (index == 1) {
            return plotly_plotter::layouts::xaxis(data_["xaxis"]);
        }
        const std::string key = "xaxis" + std::to_string(index);
        return plotly_plotter::layouts::xaxis(data_[key]);
    }

    /*!
     * \brief Access the y-axis.
     *
     * \return Y-axis.
     */
    [[nodiscard]] plotly_plotter::layouts::yaxis yaxis() {
        return plotly_plotter::layouts::yaxis(data_["yaxis"]);
    }

    /*!
     * \brief Access the y-axis.
     *
     * \param[in] index Index of the y-axis.
     * \return Y-axis.
     */
    [[nodiscard]] plotly_plotter::layouts::yaxis yaxis(std::size_t index) {
        if (index == 0) {
            throw std::out_of_range("Index of x-axis must be greater than 0");
        }
        if (index == 1) {
            return plotly_plotter::layouts::yaxis(data_["yaxis"]);
        }
        const std::string key = "yaxis" + std::to_string(index);
        return plotly_plotter::layouts::yaxis(data_[key]);
    }

    /*!
     * \brief Access the layout of the color axis.
     *
     * \return Layout of the color axis.
     */
    [[nodiscard]] plotly_plotter::layouts::color_axis color_axis() {
        return plotly_plotter::layouts::color_axis(data_["coloraxis"]);
    }

    /*!
     * \brief Access the layout of the color axis.
     *
     * \param[in] index Index of the color axis.
     * \return Layout of the color axis.
     */
    [[nodiscard]] plotly_plotter::layouts::color_axis color_axis(
        std::size_t index) {
        if (index == 0) {
            throw std::out_of_range("Index of x-axis must be greater than 0");
        }
        if (index == 1) {
            return plotly_plotter::layouts::color_axis(data_["coloraxis"]);
        }
        const std::string key = "coloraxis" + std::to_string(index);
        return plotly_plotter::layouts::color_axis(data_[key]);
    }

    /*!
     * \brief Access the title of the figure.
     *
     * \return Title of the figure.
     */
    [[nodiscard]] figure_title title() { return figure_title(data_["title"]); }

    /*!
     * \brief Access the layout of the grid.
     *
     * \return Layout of the grid.
     */
    [[nodiscard]] plotly_plotter::layouts::grid grid() {
        return plotly_plotter::layouts::grid(data_["grid"]);
    }

    /*!
     * \brief Access the legend.
     *
     * \return Legend.
     */
    [[nodiscard]] plotly_plotter::layouts::legend legend() {
        return plotly_plotter::layouts::legend(data_["legend"]);
    }

    /*!
     * \brief Append an annotation.
     *
     * \return Annotation.
     */
    [[nodiscard]] annotation add_annotation() {
        return annotation(data_["annotations"].emplace_back());
    }

    /*!
     * \brief Set the mode of showing box traces.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"group"`: group traces without overlaying
     * - `"overlay"`: overlay traces
     */
    void box_mode(std::string_view value) { data_["boxmode"] = value; }

    /*!
     * \brief Set the mode of showing violin traces.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"group"`: group traces without overlaying
     * - `"overlay"`: overlay traces
     */
    void violin_mode(std::string_view value) { data_["violinmode"] = value; }

    /*!
     * \brief Set the mode of showing bar traces.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"stack"`: stack traces
     * - `"group"`: group traces without overlaying
     * - `"overlay"`: overlay traces
     * - `"relative"`: stack traces considering negative values
     */
    void bar_mode(std::string_view value) { data_["barmode"] = value; }

    /*!
     * \brief Set whether to show the legend.
     *
     * \param[in] value Value.
     */
    void show_legend(bool value) { data_["showlegend"] = value; }

    /*!
     * \brief Set the background color of the figure.
     *
     * \param[in] value Value.
     */
    void paper_bg_color(std::string_view value) {
        data_["paper_bgcolor"] = value;
    }

    /*!
     * \brief Set the background color of the plot area.
     *
     * \param[in] value Value.
     */
    void plot_bg_color(std::string_view value) {
        data_["plot_bgcolor"] = value;
    }

    /*!
     * \brief Add a menu.
     *
     * \return Menu.
     */
    [[nodiscard]] layout_menu add_menu() {
        return layout_menu(data_["updatemenus"].emplace_back());
    }

    /*!
     * \brief Add a slider.
     *
     * \return Slider.
     */
    [[nodiscard]] layout_slider add_slider() {
        return layout_slider(data_["sliders"].emplace_back());
    }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter::layouts
