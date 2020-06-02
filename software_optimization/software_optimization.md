# Software Optimization

* [Software optimization resources](https://www.agner.org/optimize/)
* [Programming Optimization](http://www.azillionmonkeys.com/qed/optimize.html)
* [Making Your C++ Code Robust](https://www.codeproject.com/articles/216077/making-your-cplusplus-code-robust)
* [性能调优攻略](https://coolshell.cn/articles/7490.html)
* [内存管理内幕](https://www.ibm.com/developerworks/cn/linux/l-memory/)

-----

## Compiler Optimization Options

* [GCC optimization](https://wiki.gentoo.org/wiki/GCC_optimization)
* [Optimization in GCC](https://www.linuxjournal.com/article/7269)
* [GCC compiler optimization for ARM-based systems](https://gist.github.com/fm4dd/c663217935dc17f0fc73c9c81b0aa845)
* [10 useful tips for using the floating point unit on the Cortex-M4](https://community.arm.com/processors/b/blog/posts/10-useful-tips-to-using-the-floating-point-unit-on-the-arm-cortex--m4-processor)


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
