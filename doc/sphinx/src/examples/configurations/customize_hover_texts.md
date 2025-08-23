---
file_format: mystnb
---

# Customize Hover Texts

This section shows how to customize hover texts in a plot in cpp-plotly-plotter library.

## Prerequisites

- [Create a Simple Scatter Plot](../get_started/create_simple_plot.md)

## Sample Code

```{literalinclude} /../../../examples/configurations/customize_hover_texts.cpp
:caption: Example to customize hover texts in a plot.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/configurations_customize_hover_texts.html", version=2)
```

## Further Reading

- [Document of hovertemplate in Plotly.js](https://plotly.com/javascript/hover-text-and-formatting/#hovertemplate)
- API Reference:
  - {cpp:func}`plotly_plotter::traces::xy_trace_base::hover_template`
