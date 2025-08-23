---
file_format: mystnb
---

# Use Figure Builder

This sections show how to use a figure builder to create a plot in cpp-plotly-plotter library.

## Prerequisites

- [Install cpp-plotly-plotter Library](../../install.md)

## Sample Code

```{literalinclude} /../../../examples/get_started/use_figure_builder.cpp
:caption: Example to use a figure builder.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/use_figure_builder.html", version=4)
```

## Further Reading

- [Use Grouping in Figure Builders](use_grouping_in_figure_builder.md)
- [Create a Scatter Plot Using Figure Builder](../scatters/create_scatter_using_figure_builder.md)
- API Reference:
  - {cpp:class}`plotly_plotter::data_table`
  - {cpp:func}`plotly_plotter::figure_builders::line`
  - {cpp:class}`plotly_plotter::figure_builders::scatter`
  - {cpp:func}`plotly_plotter::write_html`
