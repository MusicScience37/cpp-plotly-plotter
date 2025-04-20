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

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
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
     * \brief Copy constructor.
     */
    figure_builder_base(const figure_builder_base& /*other*/) = default;

    /*!
     * \brief Move constructor.
     */
    figure_builder_base(figure_builder_base&& /*other*/) = default;

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
     * \brief Set the column name of rows in subplots.
     *
     * \param[in] value Value.
     */
    void set_subplot_row(std::string value);

    /*!
     * \brief Set the column name of columns in subplots.
     *
     * \param[in] value Value.
     */
    void set_subplot_column(std::string value);

    /*!
     * \brief Set the column name of frames in animation.
     *
     * \param[in] value Value.
     */
    void set_animation_frame(std::string value);

    /*!
     * \brief Set the column names of additional data in hovers.
     *
     * \param[in] value Value.
     */
    void set_hover_data(std::vector<std::string> value);

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
     * \param[in] num_subplot_rows Number of rows of subplots.
     * \param[in] num_subplot_columns Number of columns of subplots.
     */
    virtual void configure_axes(figure& fig, std::size_t num_subplot_rows,
        std::size_t num_subplot_columns) const = 0;

    /*!
     * \brief Get the default value of the title used when the title is not set.
     *
     * \return Title.
     */
    [[nodiscard]] virtual std::string default_title() const = 0;

    /*!
     * \brief Add a trace to a figure.
     *
     * \param[out] figure Figure to add the trace to.
     * \param[in] parent_mask Mask of the values in the parent layer.
     * \param[in] subplot_index Index of the subplot.
     * \param[in] group_name Name of the group.
     * \param[in] group_index Index of the group.
     * \param[in] hover_prefix Prefix of the hover text.
     * \param[in] additional_hover_text Additional hover text.
     */
    virtual void add_trace(figure_frame_base& figure,
        const std::vector<bool>& parent_mask, std::size_t subplot_index,
        std::string_view group_name, std::size_t group_index,
        std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const = 0;

    /*!
     * \brief Get the column names of additional data in hovers required by
     * traces.
     *
     * \return Column names.
     */
    [[nodiscard]] virtual std::vector<std::string>
    additional_hover_data_in_trace() const = 0;

private:
    /*!
     * \brief Handle animation frames.
     *
     * \param[out] fig Figure.
     * \param[in] parent_mask Mask of the values in the parent layer.
     * \param[in] hover_prefix Prefix of the hover text.
     * \param[in] additional_hover_text Additional hover text.
     * \return Number of rows and columns of subplots.
     */
    [[nodiscard]] std::pair<std::size_t, std::size_t> handle_animation_frame(
        figure& fig, const std::vector<bool>& parent_mask,
        std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const;

    /*!
     * \brief Handle rows in subplots.
     *
     * \param[out] fig Figure.
     * \param[in] is_first_frame Whether this is the first frame.
     * \param[in] parent_mask Mask of the values in the parent layer.
     * \param[in] hover_prefix Prefix of the hover text.
     * \param[in] additional_hover_text Additional hover text.
     * \return Number of rows and columns of subplots.
     */
    [[nodiscard]] std::pair<std::size_t, std::size_t> handle_subplot_row(
        figure_frame_base& fig, bool is_first_frame,
        const std::vector<bool>& parent_mask, std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const;

    /*!
     * \brief Handle columns in subplots.
     *
     * \param[out] fig Figure.
     * \param[in] is_first_frame Whether this is the first frame.
     * \param[in] parent_mask Mask of the values in the parent layer.
     * \param[in] first_subplot_index Index of the first subplot.
     * \param[in] hover_prefix Prefix of the hover text.
     * \param[in] additional_hover_text Additional hover text.
     * \return Number of subplots added.
     */
    [[nodiscard]] std::size_t handle_subplot_column(figure_frame_base& fig,
        bool is_first_frame, const std::vector<bool>& parent_mask,
        std::size_t first_subplot_index, std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const;

    /*!
     * \brief Handle groups.
     *
     * \param[out] fig Figure.
     * \param[in] is_first_frame Whether this is the first frame.
     * \param[in] parent_mask Mask of the values in the parent layer.
     * \param[in] subplot_index Index of the subplot.
     * \param[in] hover_prefix Prefix of the hover text.
     * \param[in] additional_hover_text Additional hover text.
     */
    void handle_groups(figure_frame_base& fig, bool is_first_frame,
        const std::vector<bool>& parent_mask, std::size_t subplot_index,
        std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const;

    /*!
     * \brief Add configuration common for figures with and without grouping.
     *
     * \param[out] fig Figure to configure.
     * \param[in] num_subplot_rows Number of rows of subplots.
     * \param[in] num_subplot_columns Number of columns of subplots.
     */
    void configure_figure(figure& fig, std::size_t num_subplot_rows,
        std::size_t num_subplot_columns) const;

    /*!
     * \brief Generate additional hover text.
     *
     * \return Additional hover text.
     */
    [[nodiscard]] std::vector<std::string> generate_additional_hover_text()
        const;

    //! Data.
    const data_table& data_;  // NOLINT(*-ref-data-members)

    //! Column name of groups.
    std::string group_;

    //! Column name of rows in subplots.
    std::string subplot_row_;

    //! Column name of columns in subplots.
    std::string subplot_column_;

    //! Column name of frames in animation.
    std::string animation_frame_;

    //! Column names of additional data in hovers.
    std::vector<std::string> hover_data_;

    //! Title of the figure.
    std::string title_;
};

}  // namespace plotly_plotter::figure_builders
