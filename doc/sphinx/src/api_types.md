---
file_format: mystnb
---

# Types of APIs

This library has two types of APIs.

- Traces

  - This API has full control over the plot,
    but requires more source code and sometimes requires understanding of plotly.js.

- Figure builders

  - This API is easier to use with automatic configuration by this library,
    but has less control over the plot.

Examples of both APIs are shown below using the same data.

## Example of Traces API

```{literalinclude} /../../../examples/scatters/create_grouped_scatter_using_traces.cpp
:caption: Example to create a grouped scatter plot using traces.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("examples/outputs/scatter_create_grouped_scatter_using_traces.html", version=3)
```

## Example of Figure Builders API

```{literalinclude} /../../../examples/scatters/create_scatter_using_figure_builder.cpp
:caption: Example to create a scatter plot using figure builders.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("examples/outputs/scatter_create_scatter_using_figure_builder.html", version=2)
```
