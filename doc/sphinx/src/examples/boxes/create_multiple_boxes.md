---
file_format: mystnb
---

# Create Multiple Box Plots

This section shows how to create multiple box plots using cpp-plotly-plotter library.

## Prerequisites

- [Create a Simple Box Plot](create_simple_box.md)

## Sample Code

```{literalinclude} /../../../examples/boxes/create_multiple_boxes.cpp
:caption: Example to create multiple box plots.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/boxes_create_multiple_boxes.html", version=2)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::figure_frame_base::add_box`
  - {cpp:class}`plotly_plotter::traces::box`
