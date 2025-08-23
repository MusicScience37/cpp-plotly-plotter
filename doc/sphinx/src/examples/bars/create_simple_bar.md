---
file_format: mystnb
---

# Create a Simple Bar Plot

This section shows how to create a simple bar plot using cpp-plotly-plotter library.

## Prerequisites

- [Install cpp-plotly-plotter Library](../../install.md)

## Sample Code

```{literalinclude} /../../../examples/bars/create_simple_bar.cpp
:caption: Example to create a simple bar plot.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/bars_create_simple_bar.html", version=2)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::figure_frame_base::add_bar`
  - {cpp:class}`plotly_plotter::traces::bar`
