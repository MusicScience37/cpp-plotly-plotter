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
 * \brief Definition of bar_based_histogram class.
 */
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/figure_builders/color_sequences.h"
#include "plotly_plotter/figure_builders/figure_builder_base.h"
#include "plotly_plotter/utils/calculate_histogram_bin_width.h"

namespace plotly_plotter::figure_builders {

/*!
 * \brief Class to create figures of histogram plots using bar plots in Plotly.
 *
 * \note This class hold the reference of the data.
 * So, the data must be valid until this object is destructed.
 * \note Objects of this class can't be reused.
 */
class PLOTLY_PLOTTER_EXPORT bar_based_histogram final
    : public figure_builder_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     *
     * \note This class hold the reference of the data.
     * So, the data must be valid until this object is destructed.
     */
    explicit bar_based_histogram(const data_table& data);

    /*!
     * \brief Set the column name of x coordinates (values).
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& x(std::string value);

    /*!
     * \brief Set the column name of groups.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& group(std::string value);

    /*!
     * \brief Set the column name of rows in subplots.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& subplot_row(std::string value);

    /*!
     * \brief Set the column name of columns in subplots.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& subplot_column(std::string value);

    /*!
     * \brief Set the column name of frames in animation.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& animation_frame(std::string value);

    /*!
     * \brief Set the color sequence.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& color_sequence(std::vector<std::string> value);

    /*!
     * \brief Set the fixed color.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& fixed_color(std::string value);

    /*!
     * \brief Set to change the color by group using the color sequence.
     *
     * \return This object.
     */
    bar_based_histogram& change_color_by_group();

    /*!
     * \brief Set the map of groups to colors.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& color_map(
        std::unordered_map<std::string, std::string> value);

    /*!
     * \brief Set the method to calculate bin width.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& bin_width_method(
        utils::histogram_bin_width_method value);

    /*!
     * \brief Set the fixed bin width.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& fixed_bin_width(double value);

    /*!
     * \brief Set the title of the figure.
     *
     * \param[in] value Value.
     * \return This object.
     */
    bar_based_histogram& title(std::string value);

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

    //! Type of bin counts.
    using bin_count_type = std::uint32_t;

    //! \copydoc figure_builder_base::configure_axes
    void configure_axes(figure& fig, std::size_t num_subplot_rows,
        std::size_t num_subplot_columns,
        bool require_manual_axis_ranges) const override;

    //! \copydoc figure_builder_base::default_title
    [[nodiscard]] std::string default_title() const override;

    //! \copydoc figure_builder_base::add_trace
    void add_trace(figure_frame_base& figure,
        const std::vector<bool>& parent_mask, std::size_t subplot_index,
        std::string_view group_name, std::size_t group_index,
        std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const override;

    //! \copydoc figure_builder_base::additional_hover_data_in_trace
    [[nodiscard]] std::vector<std::string> additional_hover_data_in_trace()
        const override;

    /*!
     * \brief Calculate bin edges.
     */
    void calculate_bin_edges() const;

    /*!
     * \brief Calculate bin counts.
     *
     * \param[in] mask Mask of data to calculate.
     */
    void calculate_bin_counts(const std::vector<bool>& mask) const;

    //! Color sequence.
    std::vector<std::string> color_sequence_{color_sequence_plotly()};

    //! Fixed color.
    std::string fixed_color_;

    //! Map of groups to colors.
    std::unordered_map<std::string, std::string> color_map_;

    //! Mode of coloring.
    color_mode color_mode_{color_mode::sequence};

    //! Method to calculate bin width.
    utils::histogram_bin_width_method bin_width_method_{
        utils::histogram_bin_width_method::freedman_diaconis};

    //! Fixed bin width. (Null for automatic selection.)
    mutable std::optional<double> fixed_bin_width_;

    //! Column name of x coordinates (values).
    std::string x_;

    //! Buffer of bin edges.
    mutable std::vector<double> bin_edges_;

    //! Buffer of bin centers.
    mutable std::vector<double> bin_centers_;

    //! Buffer of bin widths.
    mutable std::vector<double> bin_widths_;

    //! Buffer of bin counts.
    mutable std::vector<bin_count_type> bin_counts_;

    //! Maximum values of bin counts.
    mutable bin_count_type max_bin_count_{0};
};

}  // namespace plotly_plotter::figure_builders
