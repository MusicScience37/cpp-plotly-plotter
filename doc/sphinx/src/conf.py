"""Configuration file for Sphinx."""

# pylint: disable=invalid-name
# pylint: disable=redefined-builtin

# -- Project information -----------------------------------------------------

project = "cpp-plotly-plotter"
release = "unknown"  # inserted in command line

copyright = "2025, Kenta Kabashima. "
author = "Kenta Kabashima"

# -- General configuration ---------------------------------------------------

extensions = [
    "sphinx.ext.todo",
]

templates_path = ["_templates"]

exclude_patterns = []

# -- Options for Myst-Parser -------------------------------------------------

extensions += ["myst_parser"]

myst_enable_extensions = [
    "tasklist",
]

# -- Options for PlantUML ----------------------------------------------------

extensions += ["sphinxcontrib.plantuml"]

plantuml_output_format = "svg"
plantuml_syntax_error_image = True

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
