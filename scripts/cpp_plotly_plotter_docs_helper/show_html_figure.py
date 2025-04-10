"""Show HTML figure in Jupyter."""

import plotly.graph_objects
import plotly.offline._plotlyjs_version
from cpp_plotly_plotter_docs_helper.get_html_figure_json import get_htmL_figure_data


def _ignore(_):
    pass


def show_html_figure(html_file_path: str, version: int) -> None:
    """Show HTML figure in Jupyter.

    Args:
        html_file_path (str): File path of the HTML file.
        version (int): Version number to let caches work correctly.
    """
    _ignore(version)
    data = get_htmL_figure_data(html_file_path)
    data["layout"]["template"] = {"layout": data["template"]["layout"]}
    figure = plotly.graph_objects.Figure(data)
    figure.show(renderer="notebook_connected")
