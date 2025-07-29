# Instructions

## Basic Instructions

- In this project, all source code and documentation must be written in English.

## Commands

- To build the project, use the command `cmake --build .` in the build directory.
  Build directory is at `(project root directory)/build/Debug`.
- To test the project, use the command `ctest -V` in the build directory.
- To update Python packages, use the command `poetry add -G <group> <package_name>@latest`
  for all packages in pyproject.toml, and run `poetry update` to update all packages.
  - Do not forget to run `poetry add -G <group> <package_name>@latest`.

## Conventions

- This project uses C++17 standard.
