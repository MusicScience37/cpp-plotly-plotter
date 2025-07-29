@REM Below is used in GitLab runner in gitlab.com
@REM call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_x64

@REM Below is used in my runner.
call "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_x64

cmake .. ^
    -G Ninja ^
    -DCMAKE_CXX_COMPILER_LAUNCHER=ccache ^
    -DCMAKE_TOOLCHAIN_FILE=..\vcpkg\scripts\buildsystems\vcpkg.cmake ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DPLOTLY_PLOTTER_TESTING:BOOL=ON ^
    -DPLOTLY_PLOTTER_ENABLE_BENCH=OFF ^
    -DPLOTLY_PLOTTER_TEST_BENCHMARKS=OFF ^
    -DPLOTLY_PLOTTER_BUILD_EXAMPLES=ON ^
    -DPLOTLY_PLOTTER_TEST_EXAMPLES=ON ^
    -DPLOTLY_PLOTTER_WRITE_JUNIT:BOOL=ON

cmake --build . --config Release --parallel

ctest -V --build-config Release
