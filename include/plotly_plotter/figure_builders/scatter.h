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
 * \brief Definition of scatter class.
 */
#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/figure_builders/color_sequences.h"
#include "plotly_plotter/figure_builders/figure_builder_base.h"

namespace plotly_plotter::figure_builders {

/*!
 * \brief Class to create figures of scatter plots.
 *
 * \note This class hold the reference of the data.
 * So, the data must be valid until this object is destructed.
 * \note Objects of this class can't be reused.
 */
class PLOTLY_PLOTTER_EXPORT scatter final : public figure_builder_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     *
     * \note This class hold the reference of the data.
     * So, the data must be valid until this object is destructed.
     */
    explicit scatter(const data_table& data);

    /*!
     * \brief Set the column name of x coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& x(std::string value);

    /*!
     * \brief Set the column name of y coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& y(std::string value);

    /*!
     * \brief Set the column name of groups.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& group(std::string value);

    /*!
     * \brief Set the column names of additional data in hovers.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& hover_data(std::vector<std::string> value);

    /*!
     * \brief Set the mode of the trace.
     *
     * \param[in] value Value.
     * \return This object.
     *
     * Selection:
     *
     * - `lines`
     * - `markers`
     * - `text`
     * - Combinations of the above joined with `+`, for example `lines+markers`.
     * - `none`
     */
    scatter& mode(std::string value);

    /*!
     * \brief Set whether to use WebGL.
     *
     * \param[in] value Value.
     * \return This object.
     *
     * \note If this option is not set, this class automatically selects whether
     * to use WebGL according to the number of points.
     */
    scatter& use_web_gl(bool value);

    /*!
     * \brief Set the title of the figure.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& title(std::string value);

private:
    //! \copydoc figure_builder_base::configure_axes
    void configure_axes(figure& fig) const override;

    //! \copydoc figure_builder_base::default_title
    [[nodiscard]] std::string default_title() const override;

    //! \copydoc figure_builder_base::add_trace
    void add_trace(figure& figure, const std::vector<bool>& parent_mask,
        std::size_t xaxis_index, std::size_t yaxis_index,
        std::string_view group_name, std::size_t group_index,
        std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const override;

    /*!
     * \brief Configure a trace.
     *
     * \tparam Trace Type of the trace.
     * \param[out] scatter Scatter trace to configure.
     * \param[in] parent_mask Mask of the values in the parent layer.
     * \param[in] xaxis_index Index of the x-axis.
     * \param[in] yaxis_index Index of the y-axis.
     * \param[in] group_name Name of the group.
     * \param[in] group_index Index of the group.
     * \param[in] hover_prefix Prefix of the hover text.
     * \param[in] additional_hover_text Additional hover text.
     */
    template <typename Trace>
    void configure_trace(Trace& scatter, const std::vector<bool>& parent_mask,
        std::size_t xaxis_index, std::size_t yaxis_index,
        std::string_view group_name, std::size_t group_index,
        std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const;

    //! Column name of x coordinates.
    std::string x_;

    //! Column name of y coordinates.
    std::string y_;

    //! Mode of scatters.
    std::string mode_{"markers"};

    //! Color sequence.
    std::vector<std::string> color_sequence_{color_sequence_plotly()};

    //! Whether to use WebGL.
    std::optional<bool> use_web_gl_;
};

}  // namespace plotly_plotter::figure_builders
