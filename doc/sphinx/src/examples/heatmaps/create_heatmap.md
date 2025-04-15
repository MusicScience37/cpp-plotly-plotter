---
file_format: mystnb
---

# Create a Heatmap

This section shows how to create a heatmap in cpp-plotly-plotter library.

## Prerequisites

- [Install cpp-plotly-plotter Library](../../install.md)

## Sample Code

```{literalinclude} /../../../examples/heatmaps/create_heatmap.cpp
:caption: Example to create a heatmap.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/heatmaps_create_heatmap.html", version=1)
```

## Further Reading

- API Reference:
  - {cpp:class}`plotly_plotter::figure`
  - {cpp:class}`plotly_plotter::traces::heatmap`
  - {cpp:func}`plotly_plotter::write_html`
