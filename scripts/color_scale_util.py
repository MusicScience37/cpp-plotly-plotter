#!/usr/bin/env python3
"""Utility script of color scales."""

import pathlib

import click
import colour
import flask
import numpy
import plotly.graph_objects
import yaml

THIS_DIR = pathlib.Path(__file__).parent
COLOR_SCALE_DEF_FILE_PATH = THIS_DIR / "color_scale_def.yaml"


def load_color_scales_definition() -> dict:
    """Load color scales definition from YAML file.

    Returns:
        dict: Color scales definition.
    """
    with open(COLOR_SCALE_DEF_FILE_PATH, "r", encoding="utf-8") as file:
        return yaml.safe_load(file)


def find_color_scale_definition(color_scales_definition: dict, name: str) -> dict:
    """Find a color scale definition by name.

    Args:
        color_scales_definition (dict): Color scales definition.
        name (str): Name of the color scale.

    Returns:
        dict: Color scale definition.
    """
    for color_scale_definition in color_scales_definition["color_scales"]:
        if color_scale_definition["name"] == name:
            return color_scale_definition
    raise ValueError(f"Color scale '{name}' not found.")


def get_specification(
    color_scale_definition: dict,
) -> tuple[numpy.ndarray, numpy.ndarray, str]:
    """Get specification as numpy arrays.

    Args:
        color_scale_definition (dict): Definition of the color scale.

    Returns:
        tuple[numpy.ndarray, numpy.ndarray, str]: Normalized values, colors, and color space.
    """
    normalized_value_list: list[float] = []
    color_list: list[list[float]] = []
    for normalized_value, color in color_scale_definition["specification"][
        "values"
    ].items():
        normalized_value_list.append(float(normalized_value))
        color_list.append([float(elem) for elem in color])
    normalized_values = numpy.array(normalized_value_list)
    colors = numpy.array(color_list)
    color_space = color_scale_definition["specification"]["space"]
    return normalized_values, colors, color_space


def generate_color_scale(color_scale_definition: dict) -> list[tuple[float, str]]:
    """Generate a color scale.

    Args:
        color_scale_definition (dict): Definition of the color scale.

    Returns:
        list[tuple[float, str]]: Generated color scale.
    """
    (
        normalized_values_before_interpolation,
        colors_in_specification,
        specification_space,
    ) = get_specification(color_scale_definition)
    interpolation_space = color_scale_definition["interpolation"]["space"]
    num_interpolation_points = color_scale_definition["interpolation"]["num_points"]

    colors_before_interpolation = colour.convert(
        colors_in_specification, specification_space, interpolation_space
    )

    interpolated_normalized_values = numpy.linspace(0.0, 1.0, num_interpolation_points)
    interpolated_colors = numpy.zeros((num_interpolation_points, 3))
    for i in range(3):
        interpolated_colors[:, i] = numpy.interp(
            interpolated_normalized_values,
            normalized_values_before_interpolation,
            colors_before_interpolation[:, i],
        )

    interpolated_rgb = colour.convert(interpolated_colors, interpolation_space, "sRGB")
    interpolated_rgb[interpolated_rgb < 0] = 0
    interpolated_rgb[interpolated_rgb > 1] = 1

    interpolated_rgb_in_255 = numpy.round(interpolated_rgb * 255).astype(int)

    interpolated_color_code = [
        f"#{color[0]:02X}{color[1]:02X}{color[2]:02X}"
        for color in interpolated_rgb_in_255
    ]

    return list(zip(interpolated_normalized_values, interpolated_color_code))


@click.group()
def cli():
    """Color scale utility."""


@cli.command()
@click.argument("name")
def show(name: str) -> None:
    """Show a color scale on console."""
    print(
        generate_color_scale(
            find_color_scale_definition(load_color_scales_definition(), name)
        )
    )


def add_test_heatmap1(figure: plotly.graph_objects.Figure) -> None:
    """Add a heatmap for testing.

    Args:
        figure (plotly.graph_objects.Figure): Figure to add heatmap to.
    """
    x = numpy.linspace(0, 1, 101)
    y = numpy.linspace(0, 1, 101)
    x_grid, y_grid = numpy.meshgrid(x, y)
    coeff = 10.0
    z = (
        -numpy.exp(-coeff * ((x_grid - 0.2) ** 2 + (y_grid - 0.2) ** 2))
        + numpy.exp(-coeff * ((x_grid - 0.2) ** 2 + (y_grid - 0.8) ** 2))
        - 0.1 * numpy.exp(-coeff * ((x_grid - 0.8) ** 2 + (y_grid - 0.8) ** 2))
        + 0.1 * numpy.exp(-coeff * ((x_grid - 0.8) ** 2 + (y_grid - 0.2) ** 2))
    )
    figure.add_heatmap(
        x=x,
        y=y,
        z=z,
        coloraxis="coloraxis",
        zsmooth="best",
        xaxis="x",
        yaxis="y",
    )


def add_test_heatmap2(figure: plotly.graph_objects.Figure) -> None:
    """Add a heatmap for testing.

    Args:
        figure (plotly.graph_objects.Figure): Figure to add heatmap to.
    """
    x = numpy.linspace(-1, 1, 101)
    y = numpy.linspace(-1, 1, 101)
    x_grid, y_grid = numpy.meshgrid(x, y)
    z = numpy.atan2(y_grid, x_grid) / numpy.pi
    figure.add_heatmap(
        x=x,
        y=y,
        z=z,
        coloraxis="coloraxis",
        xaxis="x2",
        yaxis="y2",
    )


def add_test_heatmap3(figure: plotly.graph_objects.Figure) -> None:
    """Add a heatmap for testing.

    Args:
        figure (plotly.graph_objects.Figure): Figure to add heatmap to.
    """
    x = numpy.linspace(0, 1, 101)
    y = numpy.linspace(0, 1, 101)
    x_grid, y_grid = numpy.meshgrid(x, y)
    z = x_grid + y_grid - 1
    figure.add_heatmap(
        x=x,
        y=y,
        z=z,
        coloraxis="coloraxis",
        xaxis="x3",
        yaxis="y3",
    )


@cli.command()
def serve() -> None:
    """Start a server to view color scales."""
    app = flask.Flask(__name__)

    @app.route("/<name>")
    def show_color_scale(name: str) -> str:
        """Show a color scale.

        Args:
            name (str): Name of the color scale.

        Returns:
            str: HTML to view the color scale.
        """
        if name == "favicon.ico":
            flask.abort(404)

        color_scale = generate_color_scale(
            find_color_scale_definition(load_color_scales_definition(), name)
        )

        figure = plotly.graph_objects.Figure()
        add_test_heatmap1(figure)
        add_test_heatmap2(figure)
        add_test_heatmap3(figure)
        figure.update_layout(
            coloraxis={
                "colorscale": color_scale,
                "colorbar": {
                    "title": "Color Scale",
                },
                "showscale": True,
                "cmin": -1,
                "cmax": 1,
            },
            grid={
                "rows": 2,
                "columns": 2,
                "pattern": "independent",
            },
        )

        return figure.to_html(include_plotlyjs="cdn")

    app.run(debug=True, port=7621)


if __name__ == "__main__":
    cli()
