#pragma once

#include <cstddef>
#include <string>

namespace hpc {

class PosixSharedMemory {
 public:
  enum class OpenMode {
    Create,
    OpenExisting,
  };

  PosixSharedMemory(std::string name, std::size_t size, OpenMode mode);
  ~PosixSharedMemory();

  PosixSharedMemory(const PosixSharedMemory&) = delete;
  PosixSharedMemory& operator=(const PosixSharedMemory&) = delete;

  PosixSharedMemory(PosixSharedMemory&& other) noexcept;
  PosixSharedMemory& operator=(PosixSharedMemory&& other) noexcept;

  void* data() noexcept;
  const void* data() const noexcept;
  std::size_t size() const noexcept;
  const std::string& name() const noexcept;

  template <typename T>
  T* as() noexcept {
    return static_cast<T*>(data_);
  }

  static void unlink(const std::string& name);

 private:
  void close() noexcept;

  std::string name_;
  std::size_t size_{0};
  int fd_{-1};
  void* data_{nullptr};
};

}  // namespace hpc
