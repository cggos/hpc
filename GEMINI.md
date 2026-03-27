# GEMINI Context: High Performance Computing (HPC)

This directory contains a project focused on High Performance Computing (HPC) across CPU, GPU, and Assembly. It serves as both a library for HPC utilities and a collection of demonstrations and benchmarks for various optimization techniques.

## Project Overview

- **Core Technologies**: C++ (Standard 17), Assembly (8086/DOS), SIMD (Intel SSE, ARM NEON), GPU Computing (NVIDIA CUDA, OpenCL).
- **Architecture Support**: Multi-platform support for `x86-64` and `aarch64` (ARM).
- **Key Libraries**:
    - **Eigen3**: For linear algebra operations.
    - **OpenCV**: Core module used for image-related HPC tasks.
    - **GoogleTest**: For unit testing (optional).
    - **pthread**: For multi-threading and CPU affinity management.
- **Documentation**: Managed by **MkDocs** with the **Material** theme, providing an extensive guide to HPC techniques.

## Project Structure

- `Assembly/`: Legacy 8086 assembly examples for DOS.
- `cpu/`: Modern CPU optimization techniques:
    - `SIMD/`: SSE (x86) and NEON (ARM) intrinsic demonstrations.
    - `multi_threads/`: Thread pooling, OpenMP, and asynchronous programming.
    - `software_optimization/`: CPU affinity and cache testing.
- `gpu/`: GPU-accelerated computing:
    - `CUDA/`: NVIDIA-specific GPU programming.
    - `OpenCL/`: Cross-platform GPU/OpenCL programming.
- `include/hpc/`: Public headers for the core `hpc` and `hpc.common` libraries.
- `src/`: Core library implementation (CPU affinity, logging, etc.).
- `docs/`: Comprehensive documentation in Markdown.
- `test/`: Unit tests for verifying core functionality.

## Building and Running

### Build Prerequisites
- CMake 3.28+
- C++17 Compiler (GCC, Clang)
- Eigen3, OpenCV (Core)
- CUDA Toolkit (Optional, for CUDA demos)
- OpenCL (Optional, for OpenCL demos)

### Build Commands
```bash
# Standard build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Build with tests enabled
cmake -DHPC_BUILD_TEST=ON ..
make
ctest
```

### Documentation
```bash
# Local preview of the documentation site
mkdocs serve

# Generate static site
mkdocs build
```

## Development Conventions

- **Coding Style**: Based on the **Google C++ Style Guide** (see `.clang-format`).
- **Formatting**:
    - Preferred tool: `clang-format`.
    - Column limit: 120.
- **Namespacing**: All core code resides in the `hpc` namespace.
- **Logging**: Use the `hpc::Printer` class (from `hpc.common` library) for consistent logging across the project.
- **Architecture Detection**: Use `hpc/cpu/cpu.h` for processor architecture and affinity management.
- **Cross-Compilation**: Support for ARM cross-compilation is built into the CMake scripts via `cmake/build_flags.cmake`.
