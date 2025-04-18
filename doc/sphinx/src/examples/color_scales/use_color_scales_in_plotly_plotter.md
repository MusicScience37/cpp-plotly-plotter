---
file_format: mystnb
---

# Use Color Scales in cpp-plotly-plotter

This section shows how to use color scales in cpp-plotly-plotter library.

## Prerequisites

- One of the following:
  - [Create a Heatmap](../heatmaps/create_heatmap.md)
  - [Colorize Markers in Figure Builder](../scatters/colorize_markers_in_figure_builder.md)

## Use a Color Scale

```{literalinclude} /../../../examples/color_scales/use_color_scale.cpp
:caption: Example to use a color scale.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_use_color_scale.html", version=4)
```

### Neutral Color Scales Usable for General Ranges

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_neutral_color_scales.html", height=1200, version=10)
```

## Use a Color Scale for Positive Numbers

Some color scales looks better when the minimum value is set to zero.

```{literalinclude} /../../../examples/color_scales/use_positive_color_scale.cpp
:caption: Example to use a color scale for positive numbers.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_use_positive_color_scale.html", version=5)
```

### Color Scales for Positive Numbers

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_positive_color_scales.html", height=900, version=6)
```

## Use a Color Scales for Positive and Negative Numbers

Some color scales are designed for symmetric ranges of positive and negative numbers.

```{literalinclude} /../../../examples/color_scales/use_positive_negative_color_scale.cpp
:caption: Example to use a color scale for positive and negative numbers.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_use_positive_negative_color_scale.html", version=6)
```

### Color Scales for Positive and Negative Numbers

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_positive_and_negative_color_scales.html", height=1800, version=8)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::color_axis::color_scale`
  - [APIs of Color Scales](../../basic_api/color_scales.rst)
