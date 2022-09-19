# OpenMP

---


The [OpenMP](https://www.openmp.org/) API specification for parallel programming, an Application Program Interface (API) that may be used to explicitly direct **multi-threaded, shared memory parallelism**.  

OpenMP有两种常用的并行开发形式: 一是通过简单的 **fork/join** 对串行程序并行化，二是采用 **单程序多数据** 对串行程序并行化。

* [OpenMP Tutorials](https://computing.llnl.gov/tutorials/openMP/)

* [OpenMP in a nutshell](http://www.bowdoin.edu/~ltoma/teaching/cs3225-GIS/fall16/Lectures/openmp.html)


```cmake title="CMakeLists.txt"
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
```
