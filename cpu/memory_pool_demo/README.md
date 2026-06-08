# C++17 Memory Pool Demo

This demo implements a fixed-size CPU memory pool for learning allocation reuse.

## Build and Run

```bash
cmake -S cpu/memory_pool_demo -B build/memory_pool_demo
cmake --build build/memory_pool_demo -j
./build/memory_pool_demo/memory_pool_demo
```

## What It Shows

- Pre-allocating memory blocks instead of calling `new` for every object.
- Reusing freed blocks through a free list.
- Constructing and destroying C++ objects with placement new.
- Using a small RAII deleter so objects are automatically returned to the pool.

The implementation is intentionally fixed-size: one pool manages one object size and a fixed capacity. This keeps the core mechanism clear before moving to production allocators.
