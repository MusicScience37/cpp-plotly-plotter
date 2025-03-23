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
 * \brief Example to show boxes and mean lines of violin plots.
 */
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/write_html.h>

int main() {
    plotly_plotter::figure figure;

    // Create a violin trace with mean line.
    plotly_plotter::traces::violin violin = figure.add_violin();
    violin.y(std::vector{1, 2, 3, 5, 8, 13});
    violin.mean_line().visible(true);
    violin.name("Violin Plot with Mean Line");

    // Create a violin trace with box.
    violin = figure.add_violin();
    violin.y(std::vector{1, 2, 3, 5, 8, 13});
    violin.box().visible(true);
    violin.name("Violin Plot with Box");

    // Create a violin trace with both box and mean line.
    violin = figure.add_violin();
    violin.y(std::vector{1, 2, 3, 5, 8, 13});
    violin.box().visible(true);
    violin.mean_line().visible(true);
    violin.name("Violin Plot with Box and Mean Line");

    figure.title("Violin Plots with Box and Mean Line");
    plotly_plotter::write_html("violins_show_box_and_mean.html", figure);
}
