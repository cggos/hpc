# NVCC

---

## Overview

- [https://patrickorcl.medium.com/compile-with-nvcc-3566fbdfdbf](https://patrickorcl.medium.com/compile-with-nvcc-3566fbdfdbf)
- [https://arnon.dk/matching-sm-architectures-arch-and-gencode-for-various-nvidia-cards/](https://arnon.dk/matching-sm-architectures-arch-and-gencode-for-various-nvidia-cards/)
- [https://stackoverflow.com/questions/35656294/cuda-how-to-use-arch-and-code-and-sm-vs-compute](https://stackoverflow.com/questions/35656294/cuda-how-to-use-arch-and-code-and-sm-vs-compute)
- [https://www.cnblogs.com/phillee/p/12049208.html](https://www.cnblogs.com/phillee/p/12049208.html)

## Build with CMake

```cmake title="CMakeLists"
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} -O3 -std=c++11 -gencode arch=compute_52,code=sm_52)

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} -arch compute_52 -code sm_52)
```

- compute_XX 指的是 PTX 版本
- sm_XX 指的是 cubin 版本
- nvcc 的 -gencode= 命令行选项的 arch= 指定前端编译目标，并且必须始终为 PTX 版本。
- code= 指定后端编译目标，可以是 cubin 或 PTX 或两者均可。
- 只有由 code= 指定的后端目标版本将保留在结果二进制文件中，至少包含一个PTX以提供Volta兼容性


## Build OpenCV with CUDA 

```sh
#!/bin/sh
cmake \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=/opt/opencv_34 \
    -D WITH_VTK=OFF \
    -D WITH_MATLAB=OFF \
    -D WITH_TBB=ON \
    -D WITH_IPP=OFF \
    -D WITH_FFMPEG=OFF \
    -D WITH_V4L=ON \
    -D WITH_CUDA=ON \
    -D CUDA_GENERATION=Pascal \
    -D ENABLE_PRECOMPILED_HEADERS=OFF \
    -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules \
    ../opencv/
```

```title="output"
--   NVIDIA CUDA
--     Use CUFFT:                   YES
--     Use CUBLAS:                  NO
--     USE NVCUVID:                 NO
--     NVIDIA GPU arch:             30 35
--     NVIDIA PTX archs:
--     Use fast math:               NO
```
