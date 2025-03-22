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
 * \brief Definition of json_value class.
 */
#pragma once

#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <type_traits>

#include <yyjson.h>

#include "plotly_plotter/json_converter_decl.h"

namespace plotly_plotter {

/*!
 * \brief Class of JSON values.
 *
 * \note Objects of this class should be created from \ref json_document objects
 * or other \ref json_value objects.
 * \note Objects of this class doesn't manage the memory of the value,
 * so the objects can be simply copied or moved.
 */
class json_value {
public:
    /*!
     * \brief Enumeration of value types.
     */
    enum class value_type : std::uint8_t {
        //! Null.
        null,

        //! Boolean.
        boolean,

        //! Number.
        number,

        //! String.
        string,

        //! Array.
        array,

        //! Object.
        object,

        //! Other. (Types not supported by this class.)
        other
    };

    /*!
     * \brief Constructor.
     *
     * \param[in] value Value.
     * \param[in] document Document.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref json_document objects or other
     * \ref json_value objects.
     */
    json_value(yyjson_mut_val* value, yyjson_mut_doc* document) noexcept
        : value_(value), document_(document) {}

    /*!
     * \brief Copy constructor.
     */
    json_value(const json_value&) noexcept = default;

    /*!
     * \brief Move constructor.
     */
    json_value(json_value&&) noexcept = default;

    /*!
     * \brief Copy assignment operator.
     *
     * \return This object.
     */
    json_value& operator=(const json_value&) noexcept = default;

    /*!
     * \brief Move assignment operator.
     *
     * \return This object.
     */
    json_value& operator=(json_value&&) noexcept = default;

    /*!
     * \brief Destructor.
     */
    ~json_value() = default;

    /*!
     * \brief Get the type of the value.
     *
     * \return Type of the value.
     */
    [[nodiscard]] value_type type() const noexcept {
        switch (yyjson_mut_get_type(value_)) {
        case YYJSON_TYPE_NULL:
            return value_type::null;
        case YYJSON_TYPE_BOOL:
            return value_type::boolean;
        case YYJSON_TYPE_NUM:
            return value_type::number;
        case YYJSON_TYPE_STR:
            return value_type::string;
        case YYJSON_TYPE_ARR:
            return value_type::array;
        case YYJSON_TYPE_OBJ:
            return value_type::object;
        default:
            return value_type::other;
        }
    }

    /*!
     * \brief Assign a value.
     *
     * \tparam T Type of the value.
     * \param[in] value Value.
     * \return This object.
     */
    template <typename T,
        typename = std::enable_if_t<!std::is_same_v<T, json_value>>>
    json_value& operator=(const T& value) {
        json_converter<std::decay_t<T>>::to_json(value, *this);
        return *this;
    }

    /*!
     * \brief Append a value to the array.
     *
     * \tparam T Type of the value.
     * \param[in] value Value.
     *
     * \note If this object is not set, this function sets this object to an
     * array.
     */
    template <typename T>
    void push_back(const T& value) {
        set_to_array();

        json_value new_value(yyjson_mut_null(document_), document_);
        new_value = value;
        yyjson_mut_arr_append(value_, new_value.internal_value());
    }

    /*!
     * \brief Append a null value to the array and return the new value.
     *
     * \return New value.
     *
     * \note If this object is not set, this function sets this object to an
     * array.
     */
    json_value emplace_back() {
        set_to_array();

        json_value new_value(yyjson_mut_null(document_), document_);
        yyjson_mut_arr_append(value_, new_value.internal_value());
        return new_value;
    }

    /*!
     * \brief Append a key-value pair to the object or return the existing one
     * if exists.
     *
     * \param[in] key Key.
     * \return Value.
     */
    json_value operator[](std::string_view key) {
        set_to_object();

        yyjson_mut_val* existing_value =
            yyjson_mut_obj_getn(value_, key.data(), key.size());
        if (existing_value != nullptr) {
            return json_value(existing_value, document_);
        }
        json_value new_value(yyjson_mut_null(document_), document_);
        yyjson_mut_obj_add(value_,
            yyjson_mut_strncpy(document_, key.data(), key.size()),
            new_value.internal_value());
        return new_value;
    }

    /*!
     * \brief Set this value to an array.
     */
    void set_to_array() {
        if (type() == json_value::value_type::object) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }
        if (!yyjson_mut_is_arr(value_)) {
            yyjson_mut_set_arr(value_);
        }
    }

    /*!
     * \brief Set this value to an object.
     */
    void set_to_object() {
        if (type() == json_value::value_type::array) {
            throw std::runtime_error(
                "Changing the type of a value from arrays or objects is not "
                "allowed.");
        }
        if (!yyjson_mut_is_obj(value_)) {
            yyjson_mut_set_obj(value_);
        }
    }

    /*!
     * \brief Get the internal value.
     *
     * \return Internal value.
     *
     * \warning This function should not be used in ordinary user code.
     */
    [[nodiscard]] yyjson_mut_val* internal_value() const noexcept {
        return value_;
    }

    /*!
     * \brief Get the internal document.
     *
     * \return Internal document.
     *
     * \warning This function should not be used in ordinary user code.
     */
    [[nodiscard]] yyjson_mut_doc* internal_document() const noexcept {
        return document_;
    }

private:
    //! Value.
    yyjson_mut_val* value_;

    //! Document.
    yyjson_mut_doc* document_;
};

}  // namespace plotly_plotter
