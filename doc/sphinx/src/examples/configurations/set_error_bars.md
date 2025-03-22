---
file_format: mystnb
---

# Set Error Bars

THis section shows how to set error bars in cpp-plotly-plotter library.

## Prerequisites

- [Create a Simple Scatter Plot](../get_started/create_simple_plot.md)

## Sample Code

```{literalinclude} /../../../examples/configurations/set_error_bars.cpp
:caption: Example to set error bars.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/configurations_set_error_bars.html", version=1)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::traces::scatter_base::error_x`
  - {cpp:func}`plotly_plotter::traces::scatter_base::error_y`
  - {cpp:class}`plotly_plotter::traces::scatter_error`
