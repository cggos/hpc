# C++ 共享内存

## 概念

共享内存是一种进程间通信方式：多个进程把同一段物理内存映射到各自的虚拟地址空间，从而直接读写同一份数据。相比管道、消息队列或 socket，共享内存减少了内核态和用户态之间的数据拷贝，适合大数据量、低延迟的本机进程通信。

本仓库示例位于 `include/hpc/cpu/shared_memory.h`、`src/cpu/shared_memory.cpp` 和 `cpu/shared_memory_demo/`。示例使用 POSIX API：`shm_open` 创建共享内存对象，`ftruncate` 设置大小，`mmap` 映射地址，`shm_unlink` 清理对象。

## 解决的问题

- 避免多个进程之间反复复制大块数据。
- 降低本机 IPC 延迟，提高吞吐。
- 让生产者和消费者进程可以共享状态、队列或数据块。
- 支持多进程架构下的数据交换，例如采集进程、推理进程和渲染进程之间通信。

## 特点

- 共享的是内存区域，不自动提供同步。
- 指针值不能跨进程直接使用，应存储偏移量或 POD 数据。
- 生命周期需要显式管理，进程退出不等于共享内存对象自动删除。
- 需要配合 mutex、condition variable、semaphore 或 lock-free 协议保证一致性。

## 共享内存名称

POSIX 共享内存通过名字定位对象。示例中的名称是：

```cpp
constexpr char kSharedMemoryName[] = "/hpc_shared_memory_demo";
```

这个名字会传给 `shm_open` 和 `shm_unlink`：

- `shm_open(name, O_CREAT | O_EXCL | O_RDWR, 0600)`：创建一个系统级共享内存对象。
- `shm_open(name, O_RDWR, 0600)`：在另一个进程或同一程序的其他位置打开已有对象。
- `shm_unlink(name)`：删除这个名字，避免对象残留到下一次运行。

命名规则和注意点：

- 名称通常必须以 `/` 开头，例如 `/hpc_shared_memory_demo`。
- 它不是普通文件路径，但在 Linux 上通常能在 `/dev/shm/` 下看到对应对象。
- 名称需要全局唯一；如果上次异常退出且没有 `shm_unlink`，再次 `O_CREAT | O_EXCL` 创建可能失败。
- 名称只用于找到共享内存对象，不负责同步，也不描述内存里的数据结构。
- 在当前 `std::thread` demo 中，读写线程在同一进程内，其实可以直接共享指针；仍保留名称是为了演示真实 POSIX shared memory 的创建、映射和清理流程，也方便扩展为多进程版本。

## 优势

- 速度快，适合大块图像、点云、矩阵、日志缓冲区和环形队列。
- 数据布局可控，可按 cache line、页大小或业务结构组织。
- 多个进程可以同时映射同一份数据，便于拆分服务职责。

## 劣势

- 同步复杂，错误使用容易产生竞态、死锁或读取半写入数据。
- 崩溃恢复需要额外设计，例如清理残留对象和重置共享状态。
- 不适合跨机器通信。
- 对象中不能直接放普通 `std::string`、`std::vector` 等含进程私有指针的类型。

## 典型应用

- 摄像头采集进程和算法进程共享图像帧。
- 多进程推理服务共享输入/输出缓冲区。
- 高频日志、行情、传感器数据的环形缓冲区。
- CPU 与 GPU 前处理流水线中的本机进程数据交换。

## 示例说明

`shared_memory_demo` 创建一个共享结构体，写线程写入消息，读线程读取消息。示例按要求使用 `std::thread`、`std::mutex` 和 `std::condition_variable` 做线程内同步，共享数据本身仍放在 POSIX shared memory 映射区中。

需要注意：标准 C++ 的 mutex 和 condition variable 只保证在同一进程内可移植使用。真正的跨进程同步应使用 `PTHREAD_PROCESS_SHARED` 的 pthread 同步原语、POSIX semaphore，或自行设计无锁协议。

```bash
cmake -S cpu/shared_memory_demo -B build/shared_memory_demo
cmake --build build/shared_memory_demo -j
./build/shared_memory_demo/shared_memory_demo
```

使用建议：先用固定大小 POD 结构体学习机制；真实项目中再扩展为带头尾索引的 ring buffer，并给每个字段定义清晰的写入/读取协议。

## 常见错误

- 忘记调用 `shm_unlink`，导致下次创建同名对象失败。
- 在共享内存中保存裸指针、`std::string`、`std::vector` 等进程私有地址。
- 只映射共享内存但没有同步协议，读者可能看到半写入数据。
- 把 `std::mutex` 当作跨进程同步工具；标准 C++ 同步原语只适合同一进程内线程同步。
