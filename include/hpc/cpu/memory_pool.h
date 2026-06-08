#pragma once

#include <cstddef>
#include <memory>
#include <new>
#include <utility>
#include <vector>

namespace hpc {

class FixedBlockPool {
 public:
  FixedBlockPool(std::size_t block_size, std::size_t block_count);
  ~FixedBlockPool();

  FixedBlockPool(const FixedBlockPool&) = delete;
  FixedBlockPool& operator=(const FixedBlockPool&) = delete;

  void* allocate();
  void deallocate(void* ptr) noexcept;

  std::size_t capacity() const noexcept;
  std::size_t used() const noexcept;
  std::size_t available() const noexcept;

 private:
  static std::size_t align_up(std::size_t value, std::size_t alignment);

  std::size_t block_size_{};
  std::size_t block_count_{};
  void* storage_{};
  std::vector<std::byte*> free_list_;
  std::size_t used_blocks_{0};
};

template <typename T>
class ObjectPool {
 public:
  explicit ObjectPool(std::size_t capacity) : pool_(sizeof(T), capacity) {}

  template <typename... Args>
  T* create(Args&&... args) {
    void* memory = pool_.allocate();
    try {
      return new (memory) T(std::forward<Args>(args)...);
    } catch (...) {
      pool_.deallocate(memory);
      throw;
    }
  }

  void destroy(T* object) noexcept {
    if (object == nullptr) {
      return;
    }
    object->~T();
    pool_.deallocate(object);
  }

  struct Deleter {
    ObjectPool* owner{};

    void operator()(T* object) const noexcept {
      if (owner != nullptr) {
        owner->destroy(object);
      }
    }
  };

  template <typename... Args>
  std::unique_ptr<T, Deleter> make_unique(Args&&... args) {
    return std::unique_ptr<T, Deleter>(create(std::forward<Args>(args)...), Deleter{this});
  }

  std::size_t capacity() const noexcept { return pool_.capacity(); }
  std::size_t used() const noexcept { return pool_.used(); }
  std::size_t available() const noexcept { return pool_.available(); }

 private:
  FixedBlockPool pool_;
};

}  // namespace hpc
