# cpp-plotly-plotter

[![Latest Release](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-plotly-plotter/-/badges/release.svg)](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-plotly-plotter/-/releases)
[![pipeline status](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-plotly-plotter/badges/main/pipeline.svg)](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-plotly-plotter/-/commits/main)
[![coverage report](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-plotly-plotter/badges/main/coverage.svg)](https://cppplotlyplotter.musicscience37.com/coverage/)
[![C++ standard](https://img.shields.io/badge/standard-C%2B%2B17-blue?logo=c%2B%2B)](https://en.cppreference.com/w/cpp/compiler_support/17)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)

A C++ library for creating interactive plots using [Plotly](https://plotly.com/).

## Feature Overview

- Supported plots:
  - Bar plot
  - Box plot
  - Heatmap
  - Histogram
  - Line plot
  - Scatter plot
  - Violin plot
- Provides following types of APIs:
  - High-level APIs for easy plotting ("figure builders")
    - Similar to `plotly.express` in Python library of Plotly.
  - Low-level APIs to customize plots more ("traces")

## Supported Compilers

This library should compile with most C++17 compatible compilers.

Following compilers are tested in CI:

- GCC 12
- GCC 13
- Clang 19
- Clang 20
- Visual Studio 2022

## Dependencies

- [yyjson](https://github.com/ibireme/yyjson)
- [fmt](https://github.com/fmtlib/fmt)
- (Optional) [Eigen](https://gitlab.com/libeigen/eigen)

## Documentation

- [How to install this library](doc/sphinx/src/install.md)

Documentations built in CI:

| Version     | Documentation                                                        | Full API Reference (Doxygen)                                              |
| :---------- | :------------------------------------------------------------------- | :------------------------------------------------------------------------ |
| main branch | [Documentation](https://cppplotlyplotter.musicscience37.com/)        | [API Reference](https://cppplotlyplotter.musicscience37.com/api/)         |
| v0.10.1     | [Documentation](https://cppplotlyplotter.musicscience37.com/v0.10.1) | [API Reference](https://cppplotlyplotter.musicscience37.com/v0.10.1/api/) |
| v0.9.0      | [Documentation](https://cppplotlyplotter.musicscience37.com/v0.9.0)  | [API Reference](https://cppplotlyplotter.musicscience37.com/v0.9.0/api/)  |
| v0.8.0      | [Documentation](https://cppplotlyplotter.musicscience37.com/v0.8.0)  | [API Reference](https://cppplotlyplotter.musicscience37.com/v0.8.0/api/)  |
| v0.7.0      | [Documentation](https://cppplotlyplotter.musicscience37.com/v0.7.0)  | [API Reference](https://cppplotlyplotter.musicscience37.com/v0.7.0/api/)  |

## For Developers

- [How to build in the repository](doc/sphinx/src/how_to_build_in_repository.md)

### Repositories

- [GitLab (main)](https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-plotly-plotter)
- [GitHub (mirror)](https://github.com/MusicScience37/cpp-plotly-plotter)

## License

This project is licensed under [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0).
