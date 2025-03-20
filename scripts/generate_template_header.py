#!/usr/bin/env python3
"""Script to generate C++ header file fo the HTML template."""

import pathlib
import subprocess

THIS_DIR = pathlib.Path(__file__).parent
ROOT_DIR = THIS_DIR.parent
TEMPLATE_HEADER_DIR = ROOT_DIR / "include" / "plotly_plotter" / "details" / "templates"


def generate_template_header() -> None:
    """Generate the C++ header file for the HTML template."""
    html_path = THIS_DIR / "plotly_plot.html.jinja"
    with open(str(html_path), "r", encoding="utf-8") as file:
        html_contents = file.read()

    relative_html_path = html_path.relative_to(ROOT_DIR)
    header_path = TEMPLATE_HEADER_DIR / "plotly_plot_template.h"
    variable_name = "plotly_plot_template"

    with open(str(header_path), "w", encoding="utf-8") as file:
        file.write(
            rf"""/*
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
 * \brief Definition of {variable_name} variable.
 *
 * This file is generated from {relative_html_path}.
 * Change this file only via {pathlib.Path(__file__).relative_to(ROOT_DIR)} script.
 */
#pragma once

#include <string_view>

namespace plotly_plotter::details::templates {{

/*!
 * \brief HTML template for Plotly plot.
 */
static constexpr std::string_view {variable_name} = R"({html_contents})";

}}  // namespace plotly_plotter::details::templates
"""
        )

    subprocess.run(["clang-format", "-i", str(header_path)], check=True)


if __name__ == "__main__":
    generate_template_header()
