#pragma once

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

namespace hpc {

class ThreadPool {
 public:
  explicit ThreadPool(std::size_t worker_count = std::thread::hardware_concurrency());
  ~ThreadPool();

  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

  template <typename F, typename... Args>
  auto submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
    using ReturnType = std::invoke_result_t<F, Args...>;

    auto bound_task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::move(bound_task));

    std::future<ReturnType> future = task->get_future();
    {
      std::lock_guard<std::mutex> lock(mutex_);
      if (!accepting_tasks_) {
        throw std::runtime_error("submit on stopped ThreadPool");
      }
      tasks_.push([task] { (*task)(); });
    }

    task_available_.notify_one();
    return future;
  }

  std::size_t worker_count() const noexcept;

 private:
  void worker_loop();

  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> tasks_;
  mutable std::mutex mutex_;
  std::condition_variable task_available_;
  bool accepting_tasks_{true};
};

}  // namespace hpc
