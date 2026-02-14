#!/usr/bin/env python3
"""Utility script of color scales."""

import ast
import inspect
import pathlib
import subprocess

import click
import jinja2
import ok_palette_lab.plotly

THIS_DIR = pathlib.Path(__file__).parent
COLOR_SCALE_DEF_FILE_PATH = THIS_DIR / "color_scale_def.yaml"


def get_color_scale_names_and_descriptions() -> list[tuple[str, str]]:
    """Get color scale names and descriptions.

    Returns:
        list[tuple[str, str]]: Color scale names and descriptions.
    """
    source = inspect.getsource(ok_palette_lab.plotly)
    tree = ast.parse(source)

    results: list[tuple[str, str]] = []
    prev = None
    for node in tree.body:
        if isinstance(node, ast.AnnAssign):
            if isinstance(node.target, ast.Name):
                prev = node.target.id
        elif (
            prev
            and isinstance(node, ast.Expr)
            and isinstance(node.value, ast.Constant)
            and isinstance(node.value.value, str)
        ):
            results.append((prev, node.value.value))
            prev = None

    return results


def load_color_scales() -> list[dict[str, str | list[tuple[float, str]]]]:
    """Load color scales from ok_palette_lab.plotly.

    Returns:
        list[dict[str, str | list[tuple[float, str]]]]: Color scales.
    """
    color_scale_names_and_descriptions = get_color_scale_names_and_descriptions()
    color_scales: list[dict[str, str | list[tuple[float, str]]]] = []
    for name, description in color_scale_names_and_descriptions:
        color_scale: list[tuple[float, str]] = getattr(ok_palette_lab.plotly, name)
        color_scales.append(
            {
                "name": name,
                "description": description,
                "color_scale": color_scale,
            }
        )
    return color_scales


@click.group()
def cli():
    """Color scale utility."""


@cli.command()
def gen() -> None:
    """Generate C++ code for color scales."""
    data = load_color_scales()

    env = jinja2.Environment(
        loader=jinja2.FileSystemLoader(str(THIS_DIR / "templates")),
    )

    template = env.get_template("color_scales.h.jinja")
    output = THIS_DIR.parent / "include" / "plotly_plotter" / "color_scales.h"
    with open(
        str(output),
        "w",
        encoding="utf-8",
    ) as file:
        file.write(template.render(data=data))
        file.write("\n")
    subprocess.run(["clang-format", "-i", str(output)], check=True)

    template = env.get_template("color_scales.cpp.jinja")
    output = THIS_DIR.parent / "src" / "plotly_plotter" / "color_scales.cpp"
    with open(
        str(output),
        "w",
        encoding="utf-8",
    ) as file:
        file.write(template.render(data=data))
        file.write("\n")
    subprocess.run(["clang-format", "-i", str(output)], check=True)


if __name__ == "__main__":
    cli()
