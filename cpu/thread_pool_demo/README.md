# C++17 Thread Pool Demo

This demo implements a CPU thread pool in C++17.

## Build and Run

```bash
cmake -S cpu/thread_pool_demo -B build/thread_pool_demo
cmake --build build/thread_pool_demo -j
./build/thread_pool_demo/thread_pool_demo
```

## What It Shows

- A fixed number of worker threads.
- A synchronized FIFO task queue.
- `submit()` returning `std::future<T>` for task results.
- Graceful shutdown with `std::thread`, `std::condition_variable`, and explicit joins.
- Parallel CPU work on a vector workload.

This is a learning implementation. Production pools often add priorities, bounded queues, CPU affinity, task stealing, metrics, and exception policies.
