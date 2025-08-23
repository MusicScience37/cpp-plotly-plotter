---
file_format: mystnb
---

# Create a Simple Violin Plot

This section shows how to create a simple violin plot using cpp-plotly-plotter library.

## Prerequisites

- [Install cpp-plotly-plotter Library](../../install.md)

## Sample Code

```{literalinclude} /../../../examples/violins/create_simple_violin.cpp
:caption: Example to create a simple violin plot.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/violins_create_simple_violin.html", version=3)
```

## Further Reading

- [Create Multiple Violin Plots](create_multiple_violins.md)
- API Reference:
  - {cpp:func}`plotly_plotter::figure_frame_base::add_violin`
  - {cpp:class}`plotly_plotter::traces::violin`
