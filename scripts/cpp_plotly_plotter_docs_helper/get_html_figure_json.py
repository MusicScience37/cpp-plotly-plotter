#!/usr/bin/env python
"""Get JSON data of HTML figures."""

import json
import xml.etree.ElementTree as ET

import click

# Pylint generate false positives in this script.
# pylint: disable=invalid-name


def get_htmL_figure_data(html_file_path: str) -> dict:
    """Get JSON data of an HTML figure.

    Args:
        html_file_path (str): File path of the HTML file.

    Returns:
        dict: JSON data.
    """
    tree = ET.parse(html_file_path)
    root = tree.getroot()

    dataset_div = root.find(".//div[@id='dataset']")
    if dataset_div is None:
        raise ValueError("No div element with id 'dataset' found.")
    json_string = str(dataset_div.text)
    json_data = json.loads(json_string)

    return json_data


@click.command()
@click.argument("html_file_path", type=click.Path(exists=True))
def main(html_file_path: str):
    """Get JSON data of an HTML figure."""
    data = get_htmL_figure_data(html_file_path)
    print(json.dumps(data, indent=2))


if __name__ == "__main__":
    main()  # pylint: disable=E1120
