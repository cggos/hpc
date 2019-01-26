# High Performance Computing

* [StreamHPC](https://streamhpc.com/) is a software development company in parallel software for many-core processors.

* [The Supercomputing Blog](http://supercomputingblog.com/)
* [FastC++: Coding Cpp Efficiently](http://fastcpp.blogspot.com/)
* [chenguang055/multicore_gpu_programming](https://github.com/chenguang055/multicore_gpu_programming)

-----

[TOC]

# Heterogeneous Computing

* [异构开发技术社区(CSDN)](http://hc.csdn.net/)
* [Introduction to Parallel Computing](https://computing.llnl.gov/tutorials/parallel_comp/)


# MPI (Message Passing Interface)
* [MPI Forum](https://www.mpi-forum.org/): the standardization forum for MPI
* [Open MPI](https://www.open-mpi.org/): Open Source High Performance Computing.


# Concurrency

* task switching
* hardware concurrency

## Multi-Processing

### IPC

* [Interprocess Communications (Microsoft)](https://docs.microsoft.com/en-us/windows/desktop/ipc/interprocess-communications)
* [Inter-Process Communication (IPC) Introduction and Sample Code](https://www.codeproject.com/articles/34073/inter-process-communication-ipc-introduction-and-s)


## Multi-Threading

* POSIX C pthread
* boost::thread
* c++11 std::thread


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

### ARM CPU features
* [Runtime detection of CPU features on an ARMv8-A CPU](https://community.arm.com/android-community/b/android/posts/runtime-detection-of-cpu-features-on-an-armv8-a-cpu)


## CPU Benchmark

### Sysbench
[Sysbench](https://github.com/akopytov/sysbench) -- Scriptable database and system performance benchmark, a cross-platform and multi-threaded benchmark tool
```bash
sysbench --test=cpu --cpu-max-prime=20000 --num-threads=4 run
```

### [htop](http://hisham.hm/htop/) - an interactive process viewer for Unix

* [htop explained](https://peteris.rocks/blog/htop/) - Explanation of everything you can see in htop/top on Linux

![htop_up](images/htop_upper.png)
![htop_bt](images/htop_lower.png)


## CPU Instructions & Intrinsics

* [Compiler Intrinsics](https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/26td21ds(v%3dvs.100))

### Assembly
* [x86 Assembly](https://en.wikibooks.org/wiki/X86_Assembly)
* [winasm](http://www.winasm.net/): The x86 Assembly community and official home of WinAsm Studio and HiEditor
* [Easy Code Visual assembly IDE](http://www.easycode.cat/)
* [0xAX/asm](https://github.com/0xAX/asm): Learning assembly for linux-x64

### SIMD
#### Intel MMX & SSE
#### ARM NEON


## OpenMP
The [OpenMP](https://www.openmp.org/) API specification for parallel programming, an Application Program Interface (API) that may be used to explicitly direct **multi-threaded, shared memory parallelism**.  

OpenMP有两种常用的并行开发形式: 一是通过简单的 **fork/join** 对串行程序并行化，二是采用 **单程序多数据** 对串行程序并行化。

* [OpenMP Tutorials](https://computing.llnl.gov/tutorials/openMP/)
* [OpenMP in a nutshell](http://www.bowdoin.edu/~ltoma/teaching/cs3225-GIS/fall16/Lectures/openmp.html)

## OpenACC

[OpenACC](https://www.openacc.org/) is a user-driven directive-based performance-portable parallel programming model designed for scientists and engineers interested in porting their codes to a wide-variety of heterogeneous HPC hardware platforms and architectures with significantly less programming effort than required with a low-level model.

## Intel TBB

Intel [Threading Building Blocks (TBB)](https://www.threadingbuildingblocks.org/) lets you easily write parallel C++ programs that take full advantage of **multicore performance**, that are portable and composable, and that have future-proof scalability.

## Intel IPP

# GPU

* [GPU世界技术论坛](http://bbs.gpuworld.cn/forum.php)
* [General-Purpose Computation on Graphics Hardware](http://gpgpu.org/)

## GPU Benchmark

* For the Raspberry Pi GPU benchmark, use the [OpenGL 2.1 test](https://www.geeks3d.com/20160215/raspberry-pi-opengl-2-1-support-tested-with-geexlab-0-9-6-0/) that comes with GeeXLab

* [msalvaris/gpu_monitor](https://github.com/msalvaris/gpu_monitor): Monitor your GPUs whether they are on a single computer or in a cluster

## Platforms

### ARM Mali
* [ARM MALI GPU](https://streamhpc.com/knowledge/sdks/arm-mali/)

## Languages

* [CUDA vs OpenCL: Which should I use?](https://wiki.tiker.net/CudaVsOpenCL)

### OpenCL
### CUDA


# Software Optimization
* https://github.com/cggos/programming_facility/tree/master/app_build
