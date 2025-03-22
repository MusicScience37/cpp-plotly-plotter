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
 * \brief Example to set error bars.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // Create a scatter trace with error bars.
    plotly_plotter::traces::scatter scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{1.2, 2.3, 3.4});
    scatter.error_y().type("data");
    scatter.error_y().symmetric(true);
    scatter.error_y().visible(true);
    scatter.error_y().array(std::vector{0.1, 0.2, 0.3});
    scatter.name("Symmetric error bars in y");

    // Create a scatter trace with asymmetric error bars.
    scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{2.3, 3.4, 4.5});
    scatter.error_y().type("data");
    scatter.error_y().symmetric(false);
    scatter.error_y().visible(true);
    scatter.error_y().array(std::vector{0.1, 0.2, 0.3});
    scatter.error_y().array_minus(std::vector{0.2, 0.3, 0.4});
    scatter.name("Asymmetric error bars in y");

    // Create a scatter trace with error bars in x.
    scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{3.4, 4.5, 5.6});
    scatter.error_x().type("data");
    scatter.error_x().symmetric(true);
    scatter.error_x().visible(true);
    scatter.error_x().array(std::vector{0.1, 0.2, 0.3});
    scatter.name("Symmetric error bars in x");

    // Create a scatter trace with error bars in both x and y.
    scatter = figure.add_scatter();
    scatter.x(std::vector{1, 2, 3});
    scatter.y(std::vector{4.5, 5.6, 6.7});
    scatter.error_x().type("data");
    scatter.error_x().symmetric(true);
    scatter.error_x().visible(true);
    scatter.error_x().array(std::vector{0.1, 0.2, 0.3});
    scatter.error_y().type("data");
    scatter.error_y().symmetric(true);
    scatter.error_y().visible(true);
    scatter.error_y().array(std::vector{0.2, 0.3, 0.4});
    scatter.name("Symmetric error bars in x and y");

    figure.title("Scatter Plots with Error Bars");
    plotly_plotter::write_html("configurations_set_error_bars.html", figure);
}
