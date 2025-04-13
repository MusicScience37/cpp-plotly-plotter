"""Generate PDF with Playwright."""

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
