---
file_format: mystnb
---

# Create a Violin Plot Using Figure Builder

This section shows how to create a violin plot using figure builders in cpp-plotly-plotter library.

## Prerequisites

- [Use Figure Builder](../get_started/use_figure_builder.md)

## Sample Code

```{literalinclude} /../../../examples/violins/create_violins_using_figure_builder.cpp
:caption: Example to create a violin plot using figure builders.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/violins_create_violins_using_figure_builder.html", version=2)
```

## Further Reading

- API Reference:
  - {cpp:class}`plotly_plotter::data_table`
  - {cpp:class}`plotly_plotter::figure_builders::violin`
