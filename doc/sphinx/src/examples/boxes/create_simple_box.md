---
file_format: mystnb
---

# Create a Simple Box Plot

This section shows how to create a simple box plot using cpp-plotly-plotter library.

## Prerequisites

- [Install cpp-plotly-plotter Library](../../install.md)

## Sample Code

```{literalinclude} /../../../examples/boxes/create_simple_box.cpp
:caption: Example to create a simple box plot.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/boxes_create_simple_box.html", version=2)
```

## Further Reading

- [Create Multiple Box Plots](create_multiple_boxes.md)
- [Show Mean and Standard Deviation in Box Plots](show_mean_and_stddev.md)
- API Reference:
  - {cpp:func}`plotly_plotter::figure::add_box`
  - {cpp:class}`plotly_plotter::traces::box`
