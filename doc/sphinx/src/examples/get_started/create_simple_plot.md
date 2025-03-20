---
file_format: mystnb
---

# Create a Simple Scatter Plot

This section shows how to create a simple plot using cpp-plotly-plotter library.

## Prerequisites

- [Install cpp-plotly-plotter Library](../../install.md)

## Sample Code

```{literalinclude} /../../../examples/simple_plot.cpp
:caption: Example to create a simple plot.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/simple_plot.html", version=1)
```

## Further Reading

- [Add Titles to a Plot](add_titles.md)
