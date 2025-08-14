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
 * \brief Definition of plotly_histogram class.
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
 * \brief Class to create figures of histogram plots using histogram traces in
 * Plotly.
 *
 * \warning This implementation cannot handle log scale due to the limitation of
 * Plotly.
 * \note This class hold the reference of the data.
 * So, the data must be valid until this object is destructed.
 * \note Objects of this class can't be reused.
 */
class PLOTLY_PLOTTER_EXPORT plotly_histogram final
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
    explicit plotly_histogram(const data_table& data);

    /*!
     * \brief Set the column name of x coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& x(std::string value);

    /*!
     * \brief Set the column name of y coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& y(std::string value);

    /*!
     * \brief Set the column name of groups.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& group(std::string value);

    /*!
     * \brief Set the column name of rows in subplots.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& subplot_row(std::string value);

    /*!
     * \brief Set the column name of columns in subplots.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& subplot_column(std::string value);

    /*!
     * \brief Set the column name of frames in animation.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& animation_frame(std::string value);

    /*!
     * \brief Set the color sequence.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& color_sequence(std::vector<std::string> value);

    /*!
     * \brief Set the fixed color.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& fixed_color(std::string value);

    /*!
     * \brief Set to change the color by group using the color sequence.
     *
     * \return This object.
     */
    plotly_histogram& change_color_by_group();

    /*!
     * \brief Set the map of groups to colors.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& color_map(
        std::unordered_map<std::string, std::string> value);

    /*!
     * \brief Set the method to calculate bin width.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& bin_width_method(utils::histogram_bin_width_method value);

    /*!
     * \brief Set the title of the figure.
     *
     * \param[in] value Value.
     * \return This object.
     */
    plotly_histogram& title(std::string value);

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

    //! Color sequence.
    std::vector<std::string> color_sequence_{color_sequence_plotly()};

    //! Fixed color.
    std::string fixed_color_;

    //! Map of groups to colors.
    std::unordered_map<std::string, std::string> color_map_;

    //! Mode of coloring.
    color_mode color_mode_{color_mode::sequence};

    //! Method to calculate bin width.
    std::optional<utils::histogram_bin_width_method> bin_width_method_;

    //! Column name of x coordinates.
    std::string x_;

    //! Column name of y coordinates.
    std::string y_;
};

}  // namespace plotly_plotter::figure_builders
