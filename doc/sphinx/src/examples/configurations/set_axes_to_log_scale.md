---
file_format: mystnb
---

# Set Axes to Log Scale

This section shows how to set axes to log scale in cpp-plotly-plotter library.

## Prerequisites

- [Create a Simple Scatter Plot](../get_started/create_simple_plot.md)

## Sample Code

```{literalinclude} /../../../examples/configurations/set_axes_to_log_scale.cpp
:caption: Example to set axes to log scale.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/configurations_set_axes_to_log_scale.html", version=1)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::xaxis::type`
  - {cpp:func}`plotly_plotter::yaxis::type`
