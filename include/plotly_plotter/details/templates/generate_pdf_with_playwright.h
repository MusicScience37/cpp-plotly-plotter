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
 * \brief Definition of generate_pdf_with_playwright variable.
 *
 * This file is generated from scripts/generate_pdf_with_playwright.py.
 * Change this file only via scripts/generate_template_headers.py script.
 */
#pragma once

#include <string_view>

namespace plotly_plotter::details::templates {

/*!
 * \brief Python script to generate PDF with Playwright.
 */
static constexpr std::string_view generate_pdf_with_playwright =
    R"("""Generate PDF with Playwright."""

import os
import sys

import playwright.sync_api


def generate_pdf(
    input_file_path: str, output_file_path: str, width: int, height: int
) -> None:
    """Generate PDF with Playwright.

    Args:
        input_file_path (str): Path of the input HTML file.
        output_file_path (str): Path of the output PDF file.
        width (int): Width of the PDF.
        height (int): Height of the PDF.
    """
    with playwright.sync_api.sync_playwright() as pw:
        browser = pw.chromium.launch()
        page = browser.new_page()
        page.set_viewport_size({"width": width, "height": height})
        page.goto(f"file://{os.path.abspath(input_file_path)}")
        page.emulate_media(media="print")
        page.pdf(path=output_file_path, width=f"{width}px", height=f"{height}px")
        browser.close()


def _main() -> None:
    """Main function."""
    if len(sys.argv) != 5:
        print(
            "Usage: python generate_pdf_with_playwright.py "
            "<input_file_path> <output_file_path> <width> <height>"
        )
        sys.exit(1)

    input_file_path = sys.argv[1]
    output_file_path = sys.argv[2]
    width = int(sys.argv[3])
    height = int(sys.argv[4])

    generate_pdf(input_file_path, output_file_path, width, height)


if __name__ == "__main__":
    _main()
)";

}  // namespace plotly_plotter::details::templates
