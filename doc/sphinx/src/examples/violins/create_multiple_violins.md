---
file_format: mystnb
---

# Create Multiple Violin Plots

This section shows how to create multiple violin plots using cpp-plotly-plotter library.

## Prerequisites

- [Create a Simple Violin Plot](create_simple_violin.md)

## Sample Code

```{literalinclude} /../../../examples/violins/create_multiple_violins.cpp
:caption: Example to create multiple violin plots.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/violins_create_multiple_violins.html", version=1)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::figure::add_violin`
  - {cpp:class}`plotly_plotter::traces::violin`
