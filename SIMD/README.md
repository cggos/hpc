# SIMD

SIMD (Single Instruction, Multiple Data, pronounced "seem-dee") computation processes multiple data in parallel with a single instruction, resulting in significant performance improvement; 4 computations at once.

* [veclib](https://github.com/nadult/veclib): SIMD vector library for C++
* [Writing C++ Wrappers for SIMD Intrinsics](https://johanmabille.github.io/blog/2014/10/09/writing-c-plus-plus-wrappers-for-simd-intrinsics-1/)
* [SIMD(tommesani)](http://www.tommesani.com/index.php/simd/)

-----

[TOC]

## Intel MMX & SSE

* [Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide/)

### SSE(Streaming SIMD Extentions)

* [C++ - Getting started with SSE](http://felix.abecassis.me/2011/09/cpp-getting-started-with-sse/)
* [SSE - Vectorizing conditional code](https://felix.abecassis.me/2012/08/sse-vectorizing-conditional-code/)
* [SSE图像算法优化系列(cnblogs)](https://www.cnblogs.com/Imageshop/category/334067.html)

## ARM NEON

[Arm NEON](https://developer.arm.com/technologies/neon) technology is an advanced SIMD (single instruction multiple data) architecture extension for the Arm Cortex-A series and Cortex-R52 processors.

* [NEON Intrinsics Reference](https://developer.arm.com/technologies/neon/intrinsics)
* [ARM NEON Tutorial in C and Assembler](https://www.cnx-software.com/2011/11/27/arm-neon-tutorial-in-c-and-assembler/)
* [ARM NEON编程初探——一个简单的BGR888转YUV444实例详解](http://galoisplusplus.coding.me/blog/2017/06/10/use-arm-neon-to-accelerate-bgr888-to-yuv444/)

### Compiler Options

* test ARM NEON: `gcc -dM -E -x c /dev/null | grep -i -E "(SIMD|NEON|ARM)"`

#### Raspberry Pi 3 Model B
* g++ options
  ```bash
  -std=c++11 -O3 -march=native -mfpu=neon-vfpv4 -mfloat-abi=softfp -ffast-math
  ```
* for the compilation error `error: ‘vfmaq_f32’ was not declared in this scope`, you might add the option `-mfpu=neon-vfpv4` to enable `__ARM_FEATURE_FMA` in **arm_neon.h**

### Reference Books
* *NEON Programmer’s Guide*
* *ARM® NEON Intrinsics Reference*


## Converter

* [jratcliff63367/sse2neon](https://github.com/jratcliff63367/sse2neon)
* [From ARM NEON* to Intel® SSE - The Automatic Porting Solution, Tips and Tricks](https://software.intel.com/en-us/articles/from-arm-neon-to-intel-sse-the-automatic-porting-solution-tips-and-tricks)
