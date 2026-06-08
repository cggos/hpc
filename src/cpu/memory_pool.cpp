#include "hpc/cpu/memory_pool.h"

#include <stdexcept>

namespace hpc {

FixedBlockPool::FixedBlockPool(std::size_t block_size, std::size_t block_count, std::size_t alignment) {
  if (block_size == 0 || block_count == 0) {
    throw std::invalid_argument("block size and block count must be positive");
  }
  if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
    throw std::invalid_argument("alignment must be a power of two");
  }

  block_size_ = align_up(block_size, alignment);
  block_count_ = block_count;
  alignment_ = alignment;
  const auto storage_size = block_size_ * block_count_;
  storage_ = ::operator new (storage_size, std::align_val_t{alignment_});

  free_list_.reserve(block_count_);
  for (std::size_t i = 0; i < block_count_; ++i) {
    auto* block = static_cast<std::byte*>(storage_) + i * block_size_;
    free_list_.push_back(block);
  }
}

FixedBlockPool::~FixedBlockPool() { ::operator delete (storage_, std::align_val_t{alignment_}); }

void* FixedBlockPool::allocate() {
  if (free_list_.empty()) {
    throw std::bad_alloc();
  }

  void* block = free_list_.back();
  free_list_.pop_back();
  ++used_blocks_;
  return block;
}

void FixedBlockPool::deallocate(void* ptr) noexcept {
  if (ptr == nullptr) {
    return;
  }

  free_list_.push_back(static_cast<std::byte*>(ptr));
  --used_blocks_;
}

std::size_t FixedBlockPool::capacity() const noexcept { return block_count_; }

std::size_t FixedBlockPool::used() const noexcept { return used_blocks_; }

std::size_t FixedBlockPool::available() const noexcept { return free_list_.size(); }

std::size_t FixedBlockPool::align_up(std::size_t value, std::size_t alignment) {
  return (value + alignment - 1) / alignment * alignment;
}

}  // namespace hpc
