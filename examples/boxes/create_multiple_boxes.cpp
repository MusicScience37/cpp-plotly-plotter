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
 * \brief Example to create multiple box plots.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // Create a box trace.
    plotly_plotter::traces::box box = figure.add_box();
    box.y(std::vector{1, 2, 3, 5, 8, 13});
    box.name("Box1");

    // Create another box trace.
    plotly_plotter::traces::box box2 = figure.add_box();
    box2.y(std::vector{1, 3, 5, 7, 9, 11});
    box2.name("Box2");

    figure.title("Multiple Box Plots");
    plotly_plotter::write_html("boxes_create_multiple_boxes.html", figure);
}
