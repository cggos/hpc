# High Performance Computing (HPC)

[![HPC Overview](https://img.shields.io/badge/HPC-Overview-blue)](https://cgabc.xyz/2021-09-24-hpc-overview/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This repository is a comprehensive collection of High Performance Computing (HPC) techniques, benchmarks, and utility libraries covering CPU, GPU, and Assembly optimizations.

## 🚀 Features

- **CPU Optimization**:
    - **SIMD**: Intel SSE and ARM NEON intrinsic implementations.
    - **Multi-threading**: Thread pooling, OpenMP, and async/promise patterns.
    - **Software Optimization**: CPU affinity management and cache performance testing.
- **GPU Acceleration**:
    - **NVIDIA CUDA**: High-performance kernels and demos.
    - **OpenCL**: Cross-platform GPU computing examples.
- **Assembly**: Legacy 8086/DOS assembly optimization examples.
- **Utility Library**: Core C++ utilities for architecture detection and logging.

## 📂 Project Structure

- `cpu/`: Modern CPU optimization techniques (SIMD, multi-threading).
- `gpu/`: GPU computing with CUDA and OpenCL.
- `Assembly/`: Legacy 8086 assembly demos.
- `include/hpc/`: Public headers for the core HPC library.
- `src/`: Core library implementation.
- `docs/`: Extensive documentation (built with MkDocs).

## 🛠️ Build and Usage

### Prerequisites
- CMake (>= 3.28)
- C++17 Compiler (GCC/Clang)
- [Eigen3](https://eigen.tuxfamily.org/)
- [OpenCV](https://opencv.org/) (Core)
- CUDA Toolkit (Optional)

### Building the Project
```bash
# Standard build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Enable unit tests
cmake -DHPC_BUILD_TEST=ON ..
make
ctest
```

## 📖 Documentation

The documentation is managed by [MkDocs](https://www.mkdocs.org/).

```bash
# Serve documentation locally
mkdocs serve
```

Detailed guides are available in the `docs/` directory or at [hpc.cgabc.xyz](https://hpc.cgabc.xyz/).

## ⚖️ License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details (or standard MIT terms if not present).

---
*Maintained by [Gavin Gao](https://github.com/cggos)*
