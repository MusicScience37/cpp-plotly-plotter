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
 * \brief Example to show the mean and standard deviation in box plots.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // Create a box trace without showing the mean and standard deviation.
    plotly_plotter::traces::box box = figure.add_box();
    box.y(std::vector{1, 2, 3, 5, 8, 13});
    box.box_mean(false);  // This is the default behavior.
    box.name("without mean and stddev");

    // Create another box trace with showing the mean.
    box = figure.add_box();
    box.y(std::vector{1, 2, 3, 5, 8, 13});
    // Show the mean.
    box.box_mean(true);
    box.name("with mean");

    // Create another box trace with showing the standard deviation.
    box = figure.add_box();
    box.y(std::vector{1, 2, 3, 5, 8, 13});
    // Show the mean and standard deviation.
    box.box_mean("sd");
    box.name("with mean and stddev");

    figure.title("Box Plots with Mean and Standard Deviation");
    plotly_plotter::write_html("boxes_show_mean_and_stddev.html", figure);
}
