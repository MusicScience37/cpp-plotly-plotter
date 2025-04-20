---
file_format: mystnb
---

# Plot Many Points in Scatter Plot Using WebGL

This section shows how to plot many points in a scatter plot using WebGL in cpp-plotly-plotter library.

```{note}
Use of WebGL is recommended when plotting more than 1000 points
according to the document of
[plotly.express.scatter function](https://plotly.com/python-api-reference/generated/plotly.express.scatter)
in Plotly Python library.

When you use figure builders API,
this library will automatically use WebGL when the number of points is more than 1000.
```

## Prerequisites

- [Create a Simple Scatter Plot](../get_started/create_simple_plot.md)

## Sample Code

```{literalinclude} /../../../examples/scatters/plot_many_points_using_web_gl.cpp
:caption: Example to plot many points in a scatter plot using WebGL.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/scatters_plot_many_points_using_web_gl.html", version=2)
```

## Further Reading

- API Reference:
  - {cpp:class}`plotly_plotter::traces::scatter_gl`
  - {cpp:func}`plotly_plotter::figure_frame_base::add_scatter_gl`
