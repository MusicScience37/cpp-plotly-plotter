---
file_format: mystnb
---

# Show Boxes and Mean Lines of Violin Plots

This section shows how to show boxes and mean lines of violin plots using cpp-plotly-plotter library.

## Prerequisites

- [Create a Simple Violin Plot](create_simple_violin.md)

## Sample Code

```{literalinclude} /../../../examples/violins/show_box_and_mean.cpp
:caption: Example to show boxes and mean lines of violin plots.
:language: cpp
:start-at: "#include"
```

## Output

This above code will create an HTML file with a plot as shown below.

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/violins_show_box_and_mean.html", version=2)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::figure_frame_base::add_violin`
  - {cpp:class}`plotly_plotter::traces::violin`
