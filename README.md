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

* [Intel® 64 and IA-32 Architectures Software Developer Manuals](https://software.intel.com/en-us/articles/intel-sdm)
* [Hotspots, FLOPS, and uOps: To-The-Metal CPU Optimization](https://www.gdcvault.com/play/1014645/Hotspots-FLOPS-and-uOps-To)

## CPU Info
8 commands to check cpu information on Linux:  
* **/proc/cpuinfo**: The /proc/cpuinfo file contains details about individual cpu cores.
* **lscpu**: simply print the cpu hardware details in a user-friendly format
* **cpuid**: fetches **CPUID** information about Intel and AMD x86 processors
* **nproc**: just prints out the number of processing units available, note that the number of processing units might not always be the same as number of cores
* **dmidecode**: displays some information about the cpu, which includes the socket type, vendor name and various flags
* **hardinfo**: would produce a large report about many hardware parts, by reading files from the /proc directory
* **lshw -class processor**: lshw by default shows information about various hardware parts, and the '-class' option can be used to pickup information about a specific hardware part
* **inxi**: a script that uses other programs to generate a well structured easy to read report about various hardware components on the system

## CPU Benchmark
[Sysbench](https://github.com/akopytov/sysbench) -- Scriptable database and system performance benchmark, a cross-platform and multi-threaded benchmark tool
```bash
sysbench --test=cpu --cpu-max-prime=20000 --num-threads=4 run
```

## CPU Instructions & Intrinsics

* [Compiler Intrinsics](https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/26td21ds(v%3dvs.100))

### Assembly
* [x86 Assembly](https://en.wikibooks.org/wiki/X86_Assembly)
* [winasm](http://www.winasm.net/): The x86 Assembly community and official home of WinAsm Studio and HiEditor
* [Easy Code Visual assembly IDE](http://www.easycode.cat/)

### SIMD
#### Intel MMX & SSE
#### ARM NEON

## Multi Threads

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
