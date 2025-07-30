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
 * \brief Definition of classes of animation.
 */
#pragma once

#include <string_view>
#include <utility>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

namespace plotly_plotter::layouts {

/*!
 * \brief Base class of animation configuration in Plotly.
 */
class animation_base {
public:
    /*!
     * \brief Set the label of the button.
     *
     * \tparam T Type of the value.
     * \param[in] value Value.
     */
    template <typename T>
    void label(T&& value) {
        data_["label"] = std::forward<T>(value);
    }

    /*!
     * \brief Set the method of the button.
     *
     * \param[in] value Value.
     */
    void method(std::string_view value) { data_["method"] = value; }

    /*!
     * \brief Set the arguments of the method.
     *
     * \tparam T Type of the value.
     * \param[in] value Value.
     */
    template <typename T>
    void args(T&& value) {
        data_["args"] = std::forward<T>(value);
    }

protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit animation_base(json_value data) : data_(data) {
        data_.set_to_object();
    }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class of buttons in layout in Plotly.
 *
 * \note Objects of this class should be created from \ref layout_menu
 * objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class layout_menu_button : public animation_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit layout_menu_button(json_value data) : animation_base(data) {}
};

/*!
 * \brief Class of padding in layout in Plotly.
 *
 * \note Objects of this class should be created from \ref layout_menu,
 * \ref layout_slider objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class layout_pad {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit layout_pad(json_value data) : data_(data) {
        data_.set_to_object();
    }

    /*!
     * \brief Set the bottom padding.
     *
     * \param[in] value Value.
     */
    void b(double value) { data_["b"] = value; }

    /*!
     * \brief Set the left padding.
     *
     * \param[in] value Value.
     */
    void l(double value) { data_["l"] = value; }

    /*!
     * \brief Set the right padding.
     *
     * \param[in] value Value.
     */
    void r(double value) { data_["r"] = value; }

    /*!
     * \brief Set the top padding.
     *
     * \param[in] value Value.
     */
    void t(double value) { data_["t"] = value; }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class of menus in layout in Plotly.
 *
 * \note Objects of this class should be created from \ref layout objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class layout_menu {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit layout_menu(json_value data) : data_(data) {
        data_.set_to_object();
    }

    /*!
     * \brief Set the type of the menu.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"buttons"`: buttons
     * - `"dropdown"`: dropdown
     */
    void type(std::string_view value) { data_["type"] = value; }

    /*!
     * \brief Add a button.
     *
     * \return Button.
     */
    [[nodiscard]] layout_menu_button add_button() {
        return layout_menu_button(data_["buttons"].emplace_back());
    }

    /*!
     * \brief Set the anchor of the x-coordinate.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"auto"`
     * - `"left"`
     * - `"center"`
     * - `"right"`
     */
    void x_anchor(std::string_view value) { data_["xanchor"] = value; }

    /*!
     * \brief Set the anchor of the y-coordinate.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"auto"`
     * - `"top"`
     * - `"middle"`
     * - `"bottom"`
     */
    void y_anchor(std::string_view value) { data_["yanchor"] = value; }

    /*!
     * \brief Set the x-coordinate of the menu.
     *
     * \param[in] value Value.
     */
    void x(double value) { data_["x"] = value; }

    /*!
     * \brief Set the y-coordinate of the menu.
     *
     * \param[in] value Value.
     */
    void y(double value) { data_["y"] = value; }

    /*!
     * \brief Set the direction of the menu.
     *
     * \param[in] value Value.
     *
     * Selection:
     * - `"down"`: down
     * - `"up"`: up
     * - `"left"`: left
     * - `"right"`: right
     */
    void direction(std::string_view value) { data_["direction"] = value; }

    /*!
     * \brief Set the padding of the menu.
     *
     * \return Padding.
     */
    [[nodiscard]] layout_pad pad() { return layout_pad(data_["pad"]); }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class of current value of slider in Plotly.
 *
 * \note Objects of this class should be created from \ref layout_slider
 * objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class layout_slider_current_value {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref layout_slider objects.
     */
    explicit layout_slider_current_value(json_value data) : data_(data) {}

    /*!
     * \brief Set the prefix of the current value.
     *
     * \param[in] value Value.
     */
    void prefix(std::string_view value) { data_["prefix"] = value; }

    /*!
     * \brief Set whether to show the current value.
     *
     * \param[in] value Value.
     */
    void visible(bool value) { data_["visible"] = value; }

private:
    //! JSON data.
    json_value data_;
};

/*!
 * \brief Class of steps of slider in Plotly.
 *
 * \note Objects of this class should be created from \ref layout_slider
 * objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class layout_slider_step : public animation_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit layout_slider_step(json_value data) : animation_base(data) {}
};

/*!
 * \brief Class of layout of slider in Plotly.
 *
 * \note Objects of this class should be created from \ref layout objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class layout_slider {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit layout_slider(json_value data) : data_(data) {
        data_.set_to_object();
    }

    /*!
     * \brief Set the current value of the slider.
     *
     * \return Current value.
     */
    [[nodiscard]] layout_slider_current_value current_value() {
        return layout_slider_current_value(data_["currentvalue"]);
    }

    /*!
     * \brief Add a step.
     *
     * \return Step.
     */
    [[nodiscard]] layout_slider_step add_step() {
        return layout_slider_step(data_["steps"].emplace_back());
    }

    /*!
     * \brief Set the padding of the slider.
     *
     * \return Padding.
     */
    [[nodiscard]] layout_pad pad() { return layout_pad(data_["pad"]); }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter::layouts
