"""Configuration file for Sphinx."""

# pylint: disable=invalid-name
# pylint: disable=redefined-builtin

import os

THIS_DIR = os.path.dirname(os.path.abspath(__file__))

# -- Project information -----------------------------------------------------

project = "cpp-plotly-plotter"
release = "unknown"  # inserted in command line

copyright = "2025, Kenta Kabashima. "
author = "Kenta Kabashima"

# -- General configuration ---------------------------------------------------

extensions = [
    "sphinx.ext.todo",
    "sphinx_togglebutton",
]

templates_path = ["_templates"]

exclude_patterns: list = []

# -- Options for Myst-NB -----------------------------------------------------

extensions += ["myst_nb"]  # This will automatically include myst_parser

myst_enable_extensions = [
    "tasklist",
]

myst_heading_anchors = 4

nb_execution_mode = "cache"
nb_execution_cache_path = os.path.join(
    os.path.dirname(THIS_DIR), "build", "jupyter_cache"
)

# setting of MathJax
# Extension for MathJax is already enabled by myst_nb.
# MathJax URL working with Plotly was written in https://www.npmjs.com/package/plotly.js/v/3.0.1.
mathjax_path = "https://cdn.jsdelivr.net/npm/mathjax@3.2.2/es5/tex-svg.js"

# -- Options for PlantUML ----------------------------------------------------

extensions += ["sphinxcontrib.plantuml"]

plantuml_output_format = "svg"
plantuml_syntax_error_image = True

# -- Options for breathe -----------------------------------------------------

extensions += ["breathe", "sphinx.ext.graphviz"]

# this variable must be set from command line
breathe_projects = {"plotly_plotter": ""}

breathe_default_project = "plotly_plotter"

breathe_default_members = ("members",)

breathe_domain_by_extension = {
    "h": "cpp",
}

# -- Options for HTML output -------------------------------------------------

html_theme = "sphinx_orange_book_theme"
html_static_path = ["_static"]
html_title = project
html_theme_options = {
    "show_prev_next": False,
    "logo": {
        "text": html_title,
    },
    "pygment_light_style": "gruvbox-light",
    "pygment_dark_style": "native",
    "repository_url": "https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-plotly-plotter",
    "use_repository_button": True,
}

html_static_path = ["_static"]
