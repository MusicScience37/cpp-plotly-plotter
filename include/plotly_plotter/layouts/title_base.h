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
 * \brief Definition of title_base class.
 */
#pragma once

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"

namespace plotly_plotter::layouts {

/*!
 * \brief Base class of titles in Plotly.
 */
class title_base {
public:
    /*!
     * \brief Set the text of the title.
     *
     * \param[in] value Value.
     */
    void text(std::string_view value) { data_["text"] = value; }

protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit title_base(json_value data) : data_(data) {
        data_.set_to_object();
    }

    /*!
     * \brief Access the JSON data.
     *
     * \return JSON data.
     */
    [[nodiscard]] json_value data() const noexcept { return data_; }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter::layouts
