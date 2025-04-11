---
file_format: mystnb
---

# Use Grouping in Figure Builders

This section shows how to use grouping in figure builders of cpp-plotly-plotter library.

## Prerequisites

- [Use Figure Builder](use_figure_builder.md)

## Sample Codes and Outputs

### Example to Use `group` Function

```{literalinclude} /../../../examples/get_started/grouping_in_figure_builder/use_group.cpp
:caption: Example to use group function of a figure builder.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/get_started_grouping_in_figure_builder_use_group.html", version=1)
```

### Example to Use `subplot_column` Function

```{literalinclude} /../../../examples/get_started/grouping_in_figure_builder/use_subplot_column.cpp
:caption: Example to use subplot_column function of a figure builder.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/get_started_grouping_in_figure_builder_use_subplot_column.html", version=4)
```

### Example to Use `subplot_row` Function

```{literalinclude} /../../../examples/get_started/grouping_in_figure_builder/use_subplot_row.cpp
:caption: Example to use subplot_row function of a figure builder.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/get_started_grouping_in_figure_builder_use_subplot_row.html", version=1)
```

### Example to Use Multiple Groupings

```{literalinclude} /../../../examples/get_started/grouping_in_figure_builder/combine_groupings.cpp
:caption: Example to use multiple groupings of a figure builder.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/get_started_grouping_in_figure_builder_combine_groupings.html", version=2)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::figure_builders::scatter::group`
  - {cpp:func}`plotly_plotter::figure_builders::scatter::subplot_column`
  - {cpp:func}`plotly_plotter::figure_builders::scatter::subplot_row`
