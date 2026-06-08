#include "hpc/cpu/thread_pool.h"

namespace hpc {

ThreadPool::ThreadPool(std::size_t worker_count) {
  if (worker_count == 0) {
    worker_count = 1;
  }

  workers_.reserve(worker_count);
  for (std::size_t i = 0; i < worker_count; ++i) {
    workers_.emplace_back([this] { worker_loop(); });
  }
}

ThreadPool::~ThreadPool() {
  {
    std::lock_guard<std::mutex> lock(mutex_);
    accepting_tasks_ = false;
  }
  task_available_.notify_all();

  for (auto& worker : workers_) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

std::size_t ThreadPool::worker_count() const noexcept { return workers_.size(); }

void ThreadPool::worker_loop() {
  while (true) {
    std::function<void()> task;
    {
      std::unique_lock<std::mutex> lock(mutex_);
      task_available_.wait(lock, [this] { return !accepting_tasks_ || !tasks_.empty(); });

      if (tasks_.empty()) {
        if (!accepting_tasks_) {
          return;
        }
        continue;
      }

      task = std::move(tasks_.front());
      tasks_.pop();
    }

    task();
  }
}

}  // namespace hpc
