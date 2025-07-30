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
 * \brief Definition of classes of legends.
 */
#pragma once

#include <string_view>

#include "plotly_plotter/json_converter.h"  // IWYU pragma: export
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/layouts/title_base.h"

namespace plotly_plotter::layouts {

/*!
 * \brief Class of title of legend in Plotly.
 *
 * \note Objects of this class should be created from \ref legend objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class legend_title : public title_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     *
     * \warning This function should not be used in ordinary user code,
     * create objects of this class from \ref legend objects.
     */
    explicit legend_title(json_value data) : title_base(data) {}
};

/*!
 * \brief Class of legend in Plotly.
 *
 * \note Objects of this class should be created from \ref layout objects.
 * \note Objects of this class doesn't manage the memory of the data,
 * so the objects can be simply copied or moved.
 */
class legend {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data JSON data.
     */
    explicit legend(json_value data) : data_(data) { data_.set_to_object(); }

    /*!
     * \brief Access the title of the legend.
     *
     * \return Title of the legend.
     */
    [[nodiscard]] legend_title title() { return legend_title(data_["title"]); }

    /*!
     * \brief Set the vertical space (in pixels) between legend groups.
     *
     * \param[in] value Value.
     */
    void trace_group_gap(double value) { data_["tracegroupgap"] = value; }

private:
    //! JSON data.
    json_value data_;
};

}  // namespace plotly_plotter::layouts
