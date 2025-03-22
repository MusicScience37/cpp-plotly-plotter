---
file_format: mystnb
---

# Select Modes of Scatter Plots

This section shows how to select modes of scatter plots in cpp-plotly-plotter library.

## Prerequisites

- [Create a Simple Scatter Plot](../get_started/create_simple_plot.md)

## Sample Code

```{literalinclude} /../../../examples/scatters/select_modes.cpp
:caption: Example to select modes of scatter plots.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/scatter_select_modes.html", version=2)
```

## Further Reading

- API Reference:
  - {cpp:class}`plotly_plotter::traces::scatter`
