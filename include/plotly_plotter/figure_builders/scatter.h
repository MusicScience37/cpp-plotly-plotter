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
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/figure_builders/color_sequences.h"
#include "plotly_plotter/figure_builders/dash_sequences.h"
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
     * \brief Set the column name of errors in x coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& error_x(std::string value);

    /*!
     * \brief Set the column name of errors in y coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& error_y(std::string value);

    /*!
     * \brief Set the column name of negative errors in x coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     *
     * \note This function has no effect if error_x() is not set.
     */
    scatter& error_x_minus(std::string value);

    /*!
     * \brief Set the column name of negative errors in y coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     *
     * \note This function has no effect if error_y() is not set.
     */
    scatter& error_y_minus(std::string value);

    /*!
     * \brief Set the column name of colors of markers.
     *
     * \param[in] value Value.
     * \return This object.
     *
     * \note This option does not work with group().
     */
    scatter& marker_color(std::string value);

    /*!
     * \brief Set the column name of groups.
     *
     * \param[in] value Value.
     * \return This object.
     *
     * \note This option does not work with marker_color().
     */
    scatter& group(std::string value);

    /*!
     * \brief Set the column name of rows in subplots.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& subplot_row(std::string value);

    /*!
     * \brief Set the column name of columns in subplots.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& subplot_column(std::string value);

    /*!
     * \brief Set the column name of frames in animation.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& animation_frame(std::string value);

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
     * \brief Set whether to use log scale in x-axis.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& log_x(bool value);

    /*!
     * \brief Set whether to use log scale in y-axis.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& log_y(bool value);

    /*!
     * \brief Set the color sequence.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& color_sequence(std::vector<std::string> value);

    /*!
     * \brief Set the fixed color.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& fixed_color(std::string value);

    /*!
     * \brief Set to change the color by group using the color sequence.
     *
     * \return This object.
     */
    scatter& change_color_by_group();

    /*!
     * \brief Set the map of groups to colors.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& color_map(std::unordered_map<std::string, std::string> value);

    /*!
     * \brief Set the dash sequence.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& dash_sequence(std::vector<std::string> value);

    /*!
     * \brief Set the fixed dash.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& fixed_dash(std::string value);

    /*!
     * \brief Set the map of groups to dashes.
     *
     * \param[in] value Value.
     * \return This object.
     */
    scatter& dash_map(std::unordered_map<std::string, std::string> value);

    /*!
     * \brief Set to change the dash by group using the dash sequence.
     *
     * \return This object.
     */
    scatter& change_dash_by_group();

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
    //! Enumeration of modes of coloring.
    enum class color_mode : std::uint8_t {
        //! Use the fixed color.
        fixed,

        //! Use the color sequence.
        sequence,

        //! Use the color map.
        map
    };

    //! Enumeration of modes of dashes.
    enum class dash_mode : std::uint8_t {
        //! Use the fixed dash.
        fixed,

        //! Use the dash sequence.
        sequence,

        //! Use the dash map.
        map
    };

    //! \copydoc figure_builder_base::configure_axes
    void configure_axes(figure& fig, std::size_t num_subplot_rows,
        std::size_t num_subplot_columns) const override;

    //! \copydoc figure_builder_base::default_title
    [[nodiscard]] std::string default_title() const override;

    //! \copydoc figure_builder_base::add_trace
    void add_trace(figure_frame_base& figure,
        const std::vector<bool>& parent_mask, std::size_t subplot_index,
        std::string_view group_name, std::size_t group_index,
        std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const override;

    /*!
     * \brief Configure a trace.
     *
     * \tparam Trace Type of the trace.
     * \param[out] scatter Scatter trace to configure.
     * \param[in] parent_mask Mask of the values in the parent layer.
     * \param[in] subplot_index Index of the subplot.
     * \param[in] group_name Name of the group.
     * \param[in] group_index Index of the group.
     * \param[in] hover_prefix Prefix of the hover text.
     * \param[in] additional_hover_text Additional hover text.
     */
    template <typename Trace>
    void configure_trace(Trace& scatter, const std::vector<bool>& parent_mask,
        std::size_t subplot_index, std::string_view group_name,
        std::size_t group_index, std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const;

    //! \copydoc figure_builder_base::additional_hover_data_in_trace
    [[nodiscard]] std::vector<std::string> additional_hover_data_in_trace()
        const override;

    //! Column name of x coordinates.
    std::string x_;

    //! Column name of y coordinates.
    std::string y_;

    //! Column name of errors in x coordinates.
    std::string error_x_;

    //! Column name of errors in y coordinates.
    std::string error_y_;

    //! Column name of negative errors in x coordinates.
    std::string error_x_minus_;

    //! Column name of negative errors in y coordinates.
    std::string error_y_minus_;

    //! Column name of colors of markers.
    std::string marker_color_;

    //! Mode of scatters.
    std::string mode_{"markers"};

    //! Whether to use log scale in x-axis.
    bool log_x_{false};

    //! Whether to use log scale in y-axis.
    bool log_y_{false};

    //! Color sequence.
    std::vector<std::string> color_sequence_{color_sequence_plotly()};

    //! Fixed color.
    std::string fixed_color_;

    //! Map of groups to colors.
    std::unordered_map<std::string, std::string> color_map_;

    //! Mode of coloring.
    color_mode color_mode_{color_mode::sequence};

    //! Dash sequence.
    std::vector<std::string> dash_sequence_{dash_sequence_default()};

    //! Fixed dash.
    std::string fixed_dash_{"solid"};

    //! Map of groups to dashes.
    std::unordered_map<std::string, std::string> dash_map_;

    //! Mode of dashes.
    dash_mode dash_mode_{dash_mode::fixed};

    //! Whether to use WebGL.
    std::optional<bool> use_web_gl_;
};

}  // namespace plotly_plotter::figure_builders
