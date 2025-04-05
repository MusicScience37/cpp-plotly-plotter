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
 * \brief Definition of figure_builder_base class.
 */
#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/figure.h"

namespace plotly_plotter::figure_builders {

/*!
 * \brief Base class to create figures.
 *
 * \note This class hold the reference of the data.
 * So, the data must be valid until this object is destructed.
 * \note Objects of this class can't be reused.
 */
class PLOTLY_PLOTTER_EXPORT figure_builder_base {
public:
    /*!
     * \brief Create a figure.
     *
     * \return Figure.
     */
    [[nodiscard]] figure create() const;

    figure_builder_base(const figure_builder_base&) = delete;
    figure_builder_base(figure_builder_base&&) = delete;
    figure_builder_base& operator=(const figure_builder_base&) = delete;
    figure_builder_base& operator=(figure_builder_base&&) = delete;

protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     *
     * \note This class hold the reference of the data.
     * So, the data must be valid until this object is destructed.
     */
    explicit figure_builder_base(const data_table& data);

    /*!
     * \brief Destructor.
     */
    ~figure_builder_base() = default;

    /*!
     * \brief Set the column name of groups.
     *
     * \param[in] value Value.
     */
    void set_group(std::string value);

    /*!
     * \brief Set the title of the figure.
     *
     * \param[in] value Value.
     */
    void set_title(std::string value);

    /*!
     * \brief Get the data.
     *
     * \return Data.
     */
    [[nodiscard]] const data_table& data() const noexcept;

    /*!
     * \brief Configure the axes.
     *
     * \param[out] fig Figure to configure.
     */
    virtual void configure_axes(figure& fig) const = 0;

    /*!
     * \brief Get the default value of the title used when the title is not set.
     *
     * \return Title.
     */
    [[nodiscard]] virtual std::string default_title() const = 0;

    /*!
     * \brief Add a trace without grouping.
     *
     * \param[out] fig Figure to add the trace to.
     */
    virtual void add_trace_without_grouping(figure& fig) const = 0;

    /*!
     * \brief Add a trace for a group.
     *
     * \param[out] figure Figure to add the trace to.
     * \param[in] group_mask Mask of the values in the group.
     * \param[in] group_name Name of the group.
     */
    virtual void add_trace_for_group(figure& figure,
        const std::vector<bool>& group_mask,
        std::string_view group_name) const = 0;

private:
    /*!
     * \brief Create a figure without grouping.
     *
     * \return Figure.
     */
    [[nodiscard]] figure create_without_grouping() const;

    /*!
     * \brief Create a figure with grouping.
     *
     * \return Figure.
     */
    [[nodiscard]] figure create_with_grouping() const;

    //! Data.
    const data_table& data_;  // NOLINT(*-ref-data-members)

    //! Column name of groups.
    std::string group_;

    //! Title of the figure.
    std::string title_;
};

}  // namespace plotly_plotter::figure_builders
