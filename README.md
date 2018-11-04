# High Performance Computing

* [StreamHPC](https://streamhpc.com/) is a software development company in parallel software for many-core processors.
* [Open MPI](https://www.open-mpi.org/): Open Source High Performance Computing.

* [The Supercomputing Blog](http://supercomputingblog.com/)
* [FastC++: Coding Cpp Efficiently](http://fastcpp.blogspot.com/)

-----

[TOC]

# Heterogeneous Computing

* [异构开发技术社区(CSDN)](http://hc.csdn.net/)
* [Introduction to Parallel Computing](https://computing.llnl.gov/tutorials/parallel_comp/)

# CPU

## CPU Benchmark
[Sysbench](https://github.com/akopytov/sysbench) -- Scriptable database and system performance benchmark, a cross-platform and multi-threaded benchmark tool
```bash
sysbench --test=cpu --cpu-max-prime=20000 --num-threads=4 run
```

## Multi Threads

## SIMD
### Intel MMX & SSE
### ARM NEON

## OpenMP
The [OpenMP](https://www.openmp.org/) API specification for parallel programming, an Application Program Interface (API) that may be used to explicitly direct **multi-threaded, shared memory parallelism**.

* [OpenMP Tutorials](https://computing.llnl.gov/tutorials/openMP/)
* [OpenMP in a nutshell](http://www.bowdoin.edu/~ltoma/teaching/cs3225-GIS/fall16/Lectures/openmp.html)

## OpenACC

[OpenACC](https://www.openacc.org/) is a user-driven directive-based performance-portable parallel programming model designed for scientists and engineers interested in porting their codes to a wide-variety of heterogeneous HPC hardware platforms and architectures with significantly less programming effort than required with a low-level model.

## Threading Building Blocks (TBB)

Intel [Threading Building Blocks (TBB)](https://www.threadingbuildingblocks.org/) lets you easily write parallel C++ programs that take full advantage of **multicore performance**, that are portable and composable, and that have future-proof scalability.


# GPU

* [GPU世界技术论坛](http://bbs.gpuworld.cn/forum.php)
* [General-Purpose Computation on Graphics Hardware](http://gpgpu.org/)

## GPU Benchmark
For the Raspberry Pi GPU benchmark, use the [OpenGL 2.1 test](https://www.geeks3d.com/20160215/raspberry-pi-opengl-2-1-support-tested-with-geexlab-0-9-6-0/) that comes with GeeXLab

## Platforms

### ARM Mali
* [ARM MALI GPU](https://streamhpc.com/knowledge/sdks/arm-mali/)

## Languages

* [CUDA vs OpenCL: Which should I use?](https://wiki.tiker.net/CudaVsOpenCL)

### OpenCL
### CUDA


# Software Optimization
