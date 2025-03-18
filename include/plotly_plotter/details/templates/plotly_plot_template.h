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
 * \brief Definition of plotly_plot_template variable.
 *
 * This file is generated from scripts/plotly_plot.html.jinja.
 * Change this file only via scripts/generate_template_header.py script.
 */
#pragma once

#include <string_view>

namespace plotly_plotter {

/*!
 * \brief HTML template for Plotly plot.
 */
static constexpr std::string_view plotly_plot_template = R"(<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>{{ title }}</title>
        <style>
        html,
        body,
        .container {
            height: 100%;
            width: 100%;
            margin: 0px;
        }
        </style>
    </head>
    <body>
        <div id="plot" class="container"></div>
        <div id="dataset" style="display:none">{{ escaped_data }}</div>
    </body>
    <script src="https://cdn.plot.ly/plotly-3.0.1.min.js" charset="utf-8"></script>
    <script type="text/javascript">
        var dataset_str = document.querySelector('#dataset').textContent
        var dataset = JSON.parse(dataset_str);
        Plotly.newPlot("plot", dataset.data, dataset.layout, dataset.config);
    </script>
</html>
)";

}  // namespace plotly_plotter
