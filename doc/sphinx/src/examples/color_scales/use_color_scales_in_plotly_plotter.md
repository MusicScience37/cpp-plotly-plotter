---
file_format: mystnb
---

# Use Color Scales in cpp-plotly-plotter

This section shows how to use color scales in cpp-plotly-plotter library.
Color scales in this library are defined in
[OKPaletteLab](https://gitlab.com/MusicScience37Projects/utility-libraries/OKPaletteLab) library.

```{contents}
:backlinks: none
```

## Prerequisites

- One of the following:
  - [Create a Heatmap](../heatmaps/create_heatmap.md)
  - [Colorize Markers in Figure Builder](../scatters/colorize_markers_in_figure_builder.md)

## Examples

### Use a Color Scale

```{literalinclude} /../../../examples/color_scales/use_color_scale.cpp
:caption: Example to use a color scale.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_use_color_scale.html", version=5)
```

### Invert a Color Scale

```{literalinclude} /../../../examples/color_scales/invert_color_scale.cpp
:caption: Example to invert a color scale.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_invert_color_scale.html", version=7)
```

### Use a Color Scales for Positive and Negative Numbers

Some color scales are designed for symmetric ranges of positive and negative numbers.

```{literalinclude} /../../../examples/color_scales/use_positive_negative_color_scale.cpp
:caption: Example to use a color scale for positive and negative numbers.
:language: cpp
:start-at: "#include"
```

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_use_positive_negative_color_scale.html", version=7)
```

## Color Scales in cpp-plotly-plotter

### Color Scales Usable for General Ranges

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_neutral_color_scales.html", height=1500, version=11)
```

### Color Scales for Positive and Negative Numbers

```{code-cell}
:tags: ["remove-input"]

from cpp_plotly_plotter_docs_helper.show_html_figure import show_html_figure

show_html_figure("../outputs/color_scales_positive_and_negative_color_scales.html", height=1900, version=9)
```

## Further Reading

- API Reference:
  - {cpp:func}`plotly_plotter::color_axis::color_scale`
  - {cpp:func}`plotly_plotter::invert_color_scale`
  - [APIs of Color Scales](../../basic_api/color_scales.rst)
