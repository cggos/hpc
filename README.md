# High Performance Computing (HPC)

[![HPC Overview](https://img.shields.io/badge/HPC-Overview-blue)](https://cgabc.xyz/2021-09-24-hpc-overview/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This repository collects C++ HPC utilities, CPU/GPU examples, benchmarks, and notes. The core library is C++17 and focuses on reusable CPU utilities such as CPU information, thread helpers, memory pools, and thread pools. The example tree demonstrates SIMD, async/future, CPU affinity, cache behavior, CUDA, and OpenCL techniques.

## Features

- CPU utilities: architecture detection, affinity helpers, fixed-block memory pool, and thread pool.
- CPU examples: async/promise, multi-threading, thread pool, memory pool, cache tests, affinity binding, SSE, and NEON.
- GPU examples: CUDA and OpenCL demos, kept behind explicit CMake options because they require SDK/runtime support.
- Documentation: MkDocs-based guides under `docs/`.
- Legacy references: Assembly and older tutorial code are retained for study, but are not all part of the default build.

## Project Structure

- `include/hpc/`: public library headers.
- `src/`: core library implementations.
- `cpu/`: CPU examples and CPU-specific demo CMake entry.
- `gpu/`: CUDA/OpenCL examples and GPU-specific demo CMake entry.
- `docs/`: MkDocs documentation and images.
- `cmake/`: shared build flags and platform detection.
- `Assembly/`: legacy assembly examples.

## Prerequisites

- CMake 3.28+ for the root project.
- A C++17 compiler, such as GCC or Clang.
- Eigen3 and OpenCV Core for the root `hpc` library.
- CUDA Toolkit for CUDA demos, optional.
- OpenCL headers/runtime for OpenCL demos, optional.

The root build currently discovers Eigen3 and OpenCV from `CG_APP_RELEASE` and `PLATFORM_ARCH`, for example:

```bash
export CG_APP_RELEASE=/opt/user_data/apps/DevOps/app_release
export PLATFORM_ARCH=x86-64
```

## Build

Build the core libraries:

```bash
cmake -S . -B build/release
cmake --build build/release -j
```

Build the core libraries plus default CPU demos:

```bash
cmake -S . -B build/examples -DHPC_BUILD_DEMOS=ON
cmake --build build/examples -j
```

Run the new memory pool and thread pool demos:

```bash
./build/examples/cpu/memory_pool_demo/memory_pool_demo
./build/examples/cpu/thread_pool_demo/thread_pool_demo
```

## Demo Build Options

Top-level options:

- `HPC_BUILD_TEST=ON`: enable test discovery when a `test/` tree and GoogleTest are available.
- `HPC_BUILD_DEMOS=ON`: enable the `cpu/` and `gpu/` demo entry points.

CPU demo options, active when `HPC_BUILD_DEMOS=ON`:

- `HPC_BUILD_CPU_ASYNC_DEMOS=ON`
- `HPC_BUILD_CPU_MEMORY_POOL_DEMO=ON`
- `HPC_BUILD_CPU_THREAD_POOL_DEMO=ON`
- `HPC_BUILD_CPU_MULTI_THREAD_DEMOS=ON`
- `HPC_BUILD_CPU_SOFTWARE_OPT_DEMOS=ON`
- `HPC_BUILD_CPU_SIMD_DEMOS=OFF`

GPU demo options, disabled by default:

- `HPC_BUILD_OPENCL_DEMOS=ON`
- `HPC_BUILD_OPENCL_BASIC_DEMOS=ON`
- `HPC_BUILD_OPENCL_OPENCV_DEMOS=OFF`
- `HPC_BUILD_CUDA_DEMOS=ON`

Examples:

```bash
# CPU demos only
cmake -S cpu -B build/cpu_examples
cmake --build build/cpu_examples -j

# Basic OpenCL demos
cmake -S gpu/OpenCL -B build/opencl_examples
cmake --build build/opencl_examples -j

# Root build with CUDA demos
cmake -S . -B build/cuda_examples -DHPC_BUILD_DEMOS=ON -DHPC_BUILD_CUDA_DEMOS=ON
cmake --build build/cuda_examples -j
```

## Documentation

The documentation is managed by MkDocs:

```bash
mkdocs serve
mkdocs build
```

Detailed guides are available in `docs/` and at [hpc.cgabc.xyz](https://hpc.cgabc.xyz/).

## License

This project is licensed under the MIT License. See `LICENSE` if present, or use the standard MIT terms.

Maintained by [Gavin Gao](https://github.com/cggos).
