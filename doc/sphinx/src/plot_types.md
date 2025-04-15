# Types of Plots

This section shows a list of the types of plots currently available in this library.

| PLot Type | Traces API                                                                                           | Figure Builders API                                   |
| :-------- | :--------------------------------------------------------------------------------------------------- | :---------------------------------------------------- |
| Scatter   | {cpp:func}`plotly_plotter::figure::add_scatter` / {cpp:func}`plotly_plotter::figure::add_scatter_gl` | {cpp:class}`plotly_plotter::figure_builders::scatter` |
| Line      | {cpp:func}`plotly_plotter::figure::add_scatter` / {cpp:func}`plotly_plotter::figure::add_scatter_gl` | {cpp:func}`plotly_plotter::figure_builders::line`     |
| Box       | {cpp:func}`plotly_plotter::figure::add_box`                                                          | {cpp:class}`plotly_plotter::figure_builders::box`     |
| Violin    | {cpp:func}`plotly_plotter::figure::add_violin`                                                       | {cpp:class}`plotly_plotter::figure_builders::violin`  |
| Heatmap   | {cpp:func}`plotly_plotter::figure::add_heatmap`                                                      | (Not available)                                       |
