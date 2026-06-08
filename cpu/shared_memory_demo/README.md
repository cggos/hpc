# C++17 Shared Memory Demo

This demo uses POSIX shared memory with `std::thread` synchronization.

## Build and Run

```bash
cmake -S cpu/shared_memory_demo -B build/shared_memory_demo
cmake --build build/shared_memory_demo -j
./build/shared_memory_demo/shared_memory_demo
```

## What It Shows

- Creating a shared memory object with `shm_open`.
- Resizing and mapping it with `ftruncate` and `mmap`.
- Placing a C++ POD state object in shared memory.
- Coordinating a writer and reader with `std::thread`, `std::mutex`, and `std::condition_variable`.
- Cleaning up with `munmap`, `close`, and `shm_unlink`.

## Shared Memory Name

The demo uses this POSIX shared memory name:

```cpp
constexpr char kSharedMemoryName[] = "/hpc_shared_memory_demo";
```

The name is the system-level identifier passed to `shm_open()` and `shm_unlink()`. It must start with `/`, should be unique, and may appear under `/dev/shm/` on Linux. If a previous run exits before `shm_unlink()`, creating the same name with `O_CREAT | O_EXCL` can fail, so the demo tries to unlink stale state before creating it.

In this `std::thread` version, the reader and writer are in one process and could share a pointer directly. The name is kept to demonstrate the real POSIX shared memory lifecycle and to make the demo easy to extend back to a multi-process version.

For true cross-process synchronization, use process-shared pthread primitives or POSIX semaphores. Standard C++ mutexes and condition variables are only portable within one process.
