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
 * \brief Definition of violin class.
 */
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/details/plotly_plotter_export.h"
#include "plotly_plotter/figure_builders/color_sequences.h"
#include "plotly_plotter/figure_builders/figure_builder_base.h"

namespace plotly_plotter::figure_builders {

/*!
 * \brief Class to create figures of violin plots.
 *
 * \note This class hold the reference of the data.
 * So, the data must be valid until this object is destructed.
 * \note Objects of this class can't be reused.
 */
class PLOTLY_PLOTTER_EXPORT violin final : public figure_builder_base {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     *
     * \note This class hold the reference of the data.
     * So, the data must be valid until this object is destructed.
     */
    explicit violin(const data_table& data);

    /*!
     * \brief Set the column name of x coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& x(std::string value);

    /*!
     * \brief Set the column name of y coordinates.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& y(std::string value);

    /*!
     * \brief Set the column name of groups.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& group(std::string value);

    /*!
     * \brief Set the column name of rows in subplots.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& subplot_row(std::string value);

    /*!
     * \brief Set the column name of columns in subplots.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& subplot_column(std::string value);

    /*!
     * \brief Set the column names of additional data in hovers.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& hover_data(std::vector<std::string> value);

    /*!
     * \brief Set the color sequence.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& color_sequence(std::vector<std::string> value);

    /*!
     * \brief Set the fixed color.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& fixed_color(std::string value);

    /*!
     * \brief Set to change the color by group using the color sequence.
     *
     * \return This object.
     */
    violin& change_color_by_group();

    /*!
     * \brief Set the map of groups to colors.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& color_map(std::unordered_map<std::string, std::string> value);

    /*!
     * \brief Set whether to show boxes.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& show_box(bool value);

    /*!
     * \brief Set whether to show mean lines.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& show_mean_line(bool value);

    /*!
     * \brief Set how to show points.
     *
     * \param[in] value Value.
     * \return This object.
     *
     * Selection:
     * - `"all"`: show all points
     * - `"outliers"`: show only outliers
     * - `"suspectedoutliers"`: display only the outliers (method to identify
     * outliers is different with `"outliers"`)
     * - `"false"`: do not display any points
     */
    violin& points(std::string value);

    /*!
     * \brief Set whether to use log scale in y-axis.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& log_y(bool value);

    /*!
     * \brief Set the title of the figure.
     *
     * \param[in] value Value.
     * \return This object.
     */
    violin& title(std::string value);

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
        std::size_t num_subplot_columns) const override;

    //! \copydoc figure_builder_base::default_title
    [[nodiscard]] std::string default_title() const override;

    //! \copydoc figure_builder_base::add_trace
    void add_trace(figure& figure, const std::vector<bool>& parent_mask,
        std::size_t subplot_index, std::string_view group_name,
        std::size_t group_index, std::string_view hover_prefix,
        const std::vector<std::string>& additional_hover_text) const override;

    //! Color sequence.
    std::vector<std::string> color_sequence_{color_sequence_plotly()};

    //! Fixed color.
    std::string fixed_color_;

    //! Map of groups to colors.
    std::unordered_map<std::string, std::string> color_map_;

    //! Mode of coloring.
    color_mode color_mode_{color_mode::sequence};

    //! Column name of x coordinates.
    std::string x_;

    //! Column name of y coordinates.
    std::string y_;

    //! Whether to show boxes.
    bool show_box_{false};

    //! Whether to show mean lines.
    bool show_mean_line_{false};

    //! Mode to show points.
    std::string points_{"outliers"};

    //! Whether to use log scale in y-axis.
    bool log_y_{false};
};

}  // namespace plotly_plotter::figure_builders
