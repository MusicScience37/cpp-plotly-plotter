"""Run tests."""

import pathlib
import subprocess

import click


@click.command()
@click.option("--build_dir", "-b", required=True, help="Build directory.")
def run_tests(build_dir: str) -> None:
    """Run tests."""
    build_path = pathlib.Path(build_dir).absolute()
    test_temp_path = build_path / "temp_test"
    junit_dir_path = build_path / "junit"
    junit_dir_path.mkdir(parents=True, exist_ok=True)
    test_bin_path = build_path / "bin" / "plotly_plotter_test_integ_outputs"
    subprocess.run(
        [
            str(test_bin_path),
            "-r",
            "junit",
            "-o",
            str(junit_dir_path / "plotly_plotter_test_integ_outputs.xml"),
        ],
        cwd=str(test_temp_path),
        check=True,
    )


if __name__ == "__main__":
    run_tests()  # pylint: disable=no-value-for-parameter
