#include "hpc/cpu/shared_memory.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <stdexcept>
#include <utility>

namespace hpc {
namespace {

std::string make_error(const std::string& action, const std::string& name) {
  return action + " failed for shared memory object " + name;
}

}  // namespace

PosixSharedMemory::PosixSharedMemory(std::string name, std::size_t size, OpenMode mode)
    : name_(std::move(name)), size_(size) {
  if (name_.empty() || name_.front() != '/') {
    throw std::invalid_argument("POSIX shared memory name must start with '/'");
  }
  if (size_ == 0) {
    throw std::invalid_argument("shared memory size must be positive");
  }

  const int flags = (mode == OpenMode::Create) ? (O_CREAT | O_EXCL | O_RDWR) : O_RDWR;
  fd_ = shm_open(name_.c_str(), flags, 0600);
  if (fd_ < 0) {
    throw std::runtime_error(make_error("shm_open", name_));
  }

  if (mode == OpenMode::Create && ftruncate(fd_, static_cast<off_t>(size_)) != 0) {
    close();
    unlink(name_);
    throw std::runtime_error(make_error("ftruncate", name_));
  }

  data_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
  if (data_ == MAP_FAILED) {
    data_ = nullptr;
    close();
    if (mode == OpenMode::Create) {
      unlink(name_);
    }
    throw std::runtime_error(make_error("mmap", name_));
  }
}

PosixSharedMemory::~PosixSharedMemory() { close(); }

PosixSharedMemory::PosixSharedMemory(PosixSharedMemory&& other) noexcept
    : name_(std::move(other.name_)), size_(other.size_), fd_(other.fd_), data_(other.data_) {
  other.size_ = 0;
  other.fd_ = -1;
  other.data_ = nullptr;
}

PosixSharedMemory& PosixSharedMemory::operator=(PosixSharedMemory&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  close();
  name_ = std::move(other.name_);
  size_ = other.size_;
  fd_ = other.fd_;
  data_ = other.data_;

  other.size_ = 0;
  other.fd_ = -1;
  other.data_ = nullptr;
  return *this;
}

void* PosixSharedMemory::data() noexcept { return data_; }

const void* PosixSharedMemory::data() const noexcept { return data_; }

std::size_t PosixSharedMemory::size() const noexcept { return size_; }

const std::string& PosixSharedMemory::name() const noexcept { return name_; }

void PosixSharedMemory::unlink(const std::string& name) {
  if (shm_unlink(name.c_str()) != 0) {
    throw std::runtime_error(make_error("shm_unlink", name));
  }
}

void PosixSharedMemory::close() noexcept {
  if (data_ != nullptr) {
    munmap(data_, size_);
    data_ = nullptr;
  }
  if (fd_ >= 0) {
    ::close(fd_);
    fd_ = -1;
  }
}

}  // namespace hpc
