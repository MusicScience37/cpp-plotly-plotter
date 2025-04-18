---
file_format: mystnb
---

# Colorize Markers in Figure Builder

This section shows how to colorize markers in figure builders in cpp-plotly-plotter library.

## Prerequisites

- [Create a Scatter Plot Using Figure Builder](create_scatter_using_figure_builder.md)

## Sample Code

```{literalinclude} /../../../examples/scatters/colorize_markers_in_figure_builder.cpp
:caption: Example to colorize markers in a figure builder.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/scatter_colorize_markers_in_figure_builder.html", version=2)
```

## Further Reading

- [Use Color Scales in cpp-plotly-plotter](../color_scales/use_color_scales_in_plotly_plotter.md)
- API Reference:
  - {cpp:class}`plotly_plotter::data_table`
  - {cpp:class}`plotly_plotter::figure_builders::scatter`
  - {cpp:func}`plotly_plotter::figure_builders::scatter::marker_color`
