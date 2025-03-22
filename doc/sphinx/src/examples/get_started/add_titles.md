---
file_format: mystnb
---

# Add Titles to a Plot

This section shows how to add titles to a plot in cpp-plotly-plotter library.

## Prerequisites

- [Create a Simple Plot](create_simple_plot.md)

## Sample Code

```{literalinclude} /../../../examples/add_titles.cpp
:caption: Example to add titles to a plot.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/add_titles.html", version=2)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::figure_title::text`
  - {cpp:func}`plotly_plotter::axis_title::text`
