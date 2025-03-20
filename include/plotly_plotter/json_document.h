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
 * \brief Definition of json_document class.
 */
#pragma once

// IWYU pragma: no_include <cwchar>

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <utility>

#include <yyjson.h>

#include "plotly_plotter/json_value.h"

namespace plotly_plotter {

/*!
 * \brief Class of JSON documents.
 *
 * @warning Destroying this object will invalidate all json_value objects
 * created from the json_document object.
 */
class json_document {
public:
    /*!
     * \brief Constructor.
     */
    json_document() : document_(yyjson_mut_doc_new(nullptr)) {
        if (document_ == nullptr) {
            throw std::runtime_error("Failed to create a JSON document.");
        }
        root_ = yyjson_mut_null(document_);
        if (root_ == nullptr) {
            yyjson_mut_doc_free(document_);
            throw std::runtime_error("Failed to create a JSON value.");
        }
        yyjson_mut_doc_set_root(document_, root_);
    }

    json_document(const json_document&) = delete;
    json_document& operator=(const json_document&) = delete;

    /*!
     * \brief Move constructor.
     *
     * \param[in,out] other Object to move from.
     */
    json_document(json_document&& other) noexcept
        : document_(std::exchange(other.document_, nullptr)),
          root_(std::exchange(other.root_, nullptr)) {}

    /*!
     * \brief Move assignment operator.
     *
     * \param[in,out] other Object to move from.
     * \return This object.
     */
    json_document& operator=(json_document&& other) noexcept {
        if (this != &other) {
            document_ = std::exchange(other.document_, nullptr);
            root_ = std::exchange(other.root_, nullptr);
        }
        return *this;
    }

    /*!
     * \brief Destructor.
     */
    ~json_document() { yyjson_mut_doc_free(document_); }

    /*!
     * \brief Get the root value.
     *
     * \return Root value.
     */
    [[nodiscard]] json_value root() const noexcept {
        return json_value(root_, document_);
    }

    /*!
     * \brief Serialize this document to a JSON string.
     *
     * \return JSON string.
     */
    [[nodiscard]] std::string serialize_to_string() const {
        char* str = yyjson_mut_write(document_, 0, nullptr);
        if (str == nullptr) {
            throw std::runtime_error("Failed to serialize JSON document.");
        }
        std::string result(str);
        // NOLINTNEXTLINE(*-no-malloc): Required by an external library.
        std::free(str);
        return result;
    }

    /*!
     * \brief Serialize this document to a file.
     *
     * \param[in,out] file File to write.
     */
    void serialize_to(std::FILE* file) const {
        if (!yyjson_mut_write_fp(file, document_, 0, nullptr, nullptr)) {
            throw std::runtime_error("Failed to serialize JSON document.");
        }
    }

private:
    //! Document.
    yyjson_mut_doc* document_;

    //! Root value.
    yyjson_mut_val* root_{};
};

}  // namespace plotly_plotter
