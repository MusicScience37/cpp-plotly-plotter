"""Show HTML figure in Jupyter."""

import plotly.graph_objects
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
    template = {"data": {}, "layout": data["template"]["layout"]}
    for trace in data["template"]["data"]:
        trace_type = trace["type"]
        if trace_type not in template["data"]:
            template["data"][trace_type] = []
        template["data"][trace_type].append(trace)
    data["layout"]["template"] = template
    figure = plotly.graph_objects.Figure(data, skip_invalid=True)
    figure.show(renderer="notebook_connected")
