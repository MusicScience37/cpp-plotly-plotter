---
file_format: mystnb
---

# Show Mean and Standard Deviation in Box Plots

This section shows how to show mean and standard deviation in box plots using cpp-plotly-plotter library.

## Prerequisites

- [Create a Simple Box Plot](create_simple_box.md)

## Sample Code

```{literalinclude} /../../../examples/boxes/show_mean_and_stddev.cpp
:caption: Example to show the mean and standard deviation in box plots.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/boxes_show_mean_and_stddev.html", version=2)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::figure_frame_base::add_box`
  - {cpp:class}`plotly_plotter::traces::box`
