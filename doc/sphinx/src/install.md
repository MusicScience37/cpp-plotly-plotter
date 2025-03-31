# Install cpp-plotly-plotter Library

This library can be installed only via vcpkg currently.

## Via vcpkg

This library can be installed via [vcpkg](https://vcpkg.io/) using following configurations:

- Add a vcpkg registry
  `https://gitlab.com/MusicScience37Projects/vcpkg-registry`
  in `vcpkg-configuration.json`.

  Example:

  ```json
  {
    "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg-configuration.schema.json",
    "default-registry": {
      "kind": "builtin",
      "baseline": "acd5bba5aac8b6573b5f6f463dc0341ac0ee6fa4"
    },
    "registries": [
      {
        "kind": "git",
        "repository": "https://gitlab.com/MusicScience37Projects/vcpkg-registry",
        "baseline": "3ef342fb166862105dbb176c83281c3f260e26b8",
        "packages": ["cpp-plotly-plotter"]
      }
    ]
  }
  ```

- Add `cpp-plotly-plotter` in `vcpkg.json`

  Example:

  ```json
  {
    "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg.schema.json",
    "dependencies": ["cpp-plotly-plotter"]
  }
  ```

## Further Reading

- [Create a Simple Scatter Plot](./examples/get_started/create_simple_plot.md)
