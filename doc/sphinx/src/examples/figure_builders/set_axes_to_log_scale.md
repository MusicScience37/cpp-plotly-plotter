---
file_format: mystnb
---

# Set Axes to Log Scale in Figure Builder

This section shows how to set the axes to log scale in a figure builder using the cpp-plotly-plotter library.

## Prerequisites

- [Use Figure Builder](../get_started/use_figure_builder.md)

## Sample Code

```{literalinclude} /../../../examples/figure_builders/set_axes_to_log_scale.cpp
:caption: Example to set axes to log scale.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/figure_builders_set_axes_to_log_scale.html", version=1)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::figure_builders::scatter::log_x`
  - {cpp:func}`plotly_plotter::figure_builders::scatter::log_y`
