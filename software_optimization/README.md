# Software Optimization
Software Analysis, Debug and Optimization

-----

## [htop](http://hisham.hm/htop/) - an interactive process viewer for Unix

* [htop explained](https://peteris.rocks/blog/htop/) - Explanation of everything you can see in htop/top on Linux

![htop_up](images/htop_upper.png)
![htop_bt](images/htop_lower.png)


## Cppcheck - a static analysis tool for C/C++ code
[Cppcheck](http://cppcheck.sourceforge.net/) provides unique code analysis to detect bugs and focuses on detecting undefined behaviour and dangerous coding constructs. The goal is to detect only real errors in the code (i.e. have very few false positives).
```
cppcheck --enable=all src/
```


## Valgrind - a dynamic analysis tools
[Valgrind](http://valgrind.org/) is an instrumentation framework for building dynamic analysis tools. There are Valgrind tools that can **automatically detect many memory management and threading bugs, and profile your programs in detail**. You can also use Valgrind to build new tools.
```
valgrind --tool=memcheck --leak-check=full <program args>
```


## gprof and gcov

[gprof and gcov](https://alex.dzyoba.com/blog/gprof-gcov/) are classical profilers that are still in use. Since the dawn of time, they were used by hackers to gain insight into their programs at the source code level.

* **[gprof](https://sourceware.org/binutils/docs/gprof/) (GNU Profiler)** – simple and easy profiler that can show how much time your program spends in routines in percents and seconds. gprof uses source code instrumentation by inserting special mcount function call to gather metrics of your program.
```
gprof <program_name> gmon.out
```

* **[gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) (short for GNU Coverage)** is a tool you can use in conjunction with GCC to test code coverage in your programs. Usually it’s used in pair with gprof to understand what exact line in slacking function is holds your program down.
```
gcov -b *.gcno
```

* [cpp-coveralls](https://github.com/eddyxu/cpp-coveralls) - Upload C/C++ coverage report to coveralls.io


## [GTest](https://github.com/google/googletest) - Google C++ Testing Framework
* [Getting started with Google Test (GTest) on Ubuntu](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)
* [玩转Google开源C++单元测试框架Google Test系列(gtest)(总)](http://www.cnblogs.com/coderzh/archive/2009/04/06/1426755.html)


## Others
* for循环
  - 重点优化计算量大的for循环
* 内存
  - 减少内存的重复开辟
* 使用std::vector
  - 调用push_back前，使用reserve方法预分配内存
  - 使用resize方法初始化vector，再使用=赋值
* 查表法
  - 一些函数可以用查表法线性近似，必要时还可以动底层的数学计算库
