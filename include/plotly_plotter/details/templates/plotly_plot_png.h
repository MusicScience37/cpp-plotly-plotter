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
 * \brief Definition of plotly_plot_png variable.
 *
 * This file is generated from scripts/templates/plotly_plot_png.html.jinja.
 * Change this file only via scripts/generate_template_headers.py script.
 */
#pragma once

#include <string_view>

namespace plotly_plotter::details::templates {

/*!
 * \brief HTML template for plots in Plotly for PNG generation.
 */
static constexpr std::string_view plotly_plot_png = R"(<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>{{ title }}</title>
    </head>
    <body>
        <div id="plot" class="plotly-plotter-container"></div>
        <div id="dataset" class="plotly-plotter-hide">{{ escaped_data }}</div>
    </body>
    <style>
        html, body, .plotly-plotter-container {
            height: 100%;
            width: 100%;
            margin: 0px;
            padding: 0px;
        }

        .plotly-plotter-hide {
            display: none;
        }
    </style>
    <script src="https://cdn.jsdelivr.net/npm/mathjax@3.2.2/es5/tex-svg.js"></script>
    <script src="https://cdn.plot.ly/plotly-3.0.1.min.js" charset="utf-8"></script>
    <script type="text/javascript">
        var dataset_str = document.querySelector('#dataset').textContent;
        var dataset = JSON.parse(dataset_str);
        var config = dataset.config;
        config.scrollZoom = false;
        config.responsive = true;
        config.displayModeBar = false;
        var layout = dataset.layout;
        layout.template = Plotly.makeTemplate(dataset.template);
        Plotly.newPlot("plot", dataset.data, layout, config);
    </script>
</html>
)";

}  // namespace plotly_plotter::details::templates
