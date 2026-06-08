# Repository Guidelines

## Project Structure & Module Organization

This repository combines HPC utility libraries, examples, benchmarks, and documentation. Core public headers live under `include/hpc/`, with implementations in `src/` (`src/common`, `src/cpu`). CPU examples are in `cpu/`, including SIMD, thread pool, async, and cache/affinity demos. GPU examples are in `gpu/`, split between `CUDA/` and `OpenCL/`. Legacy assembly samples are in `Assembly/`. Documentation is maintained in `docs/` and configured by `mkdocs.yml`; image assets are under `docs/img/`.

## Build, Test, and Development Commands

- `mkdir -p build && cd build && cmake ..`: configure the default CMake build.
- `cmake --build build -j`: build the `hpc` and `hpc.common` shared libraries.
- `cmake -S . -B build -DHPC_BUILD_TEST=ON`: configure with GoogleTest support when a `test/` tree is available.
- `ctest --test-dir build`: run CTest-discovered tests.
- `mkdocs serve`: preview the documentation site locally.
- `mkdocs build`: generate the static documentation site.

CMake expects Eigen3 and OpenCV paths from `CG_APP_RELEASE` and `PLATFORM_ARCH`; verify those environment variables before configuring.

## Coding Style & Naming Conventions

C++ code follows Google C++ style via `.clang-format` with a 120-column limit. Run `clang-format` before submitting changes. Prefer `.cpp` for C++ sources, `.cc` where existing examples already use it, `.cu` for CUDA, and `.cl` for OpenCL kernels. Keep public API in `include/hpc/...`, implementation in matching `src/...` paths, and use the `hpc` namespace for core library code.

## Testing Guidelines

Unit testing is wired through CMake with `HPC_BUILD_TEST` and optional GoogleTest discovery. Place new tests under `test/` with descriptive names such as `test_cpu_affinity.cpp` or `test_logger.cpp`, then register them from `test/CMakeLists.txt`. For hardware-specific CUDA, OpenCL, SIMD, or affinity changes, document the tested architecture, driver/runtime version, and any skipped cases.

## Commit & Pull Request Guidelines

Recent history uses short conventional prefixes such as `feat:`, `fix:`, `docs:`, `style:`, and `refactor:`. Keep commit subjects concise and imperative, for example `fix: lib path error`. Pull requests should describe the change, list build/test commands run, link related issues when applicable, and include screenshots only for documentation or visual output changes.

## Agent-Specific Instructions

Keep generated changes scoped. Do not modify vendored or legacy example trees such as `cpu/SIMD/sse_guide_cpp/Scons/` unless the task specifically targets them. Prefer updating docs alongside code when behavior, build requirements, or example usage changes.
