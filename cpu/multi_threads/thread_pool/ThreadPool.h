/**
 * @file ThreadPool00.h
 * @author Gavin Gao (cggos@outlook.com)
 * @brief A simple C++11 Thread Pool implementation
 * @ref https://github.com/progschj/ThreadPool
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

class ThreadPool {
 public:
  ThreadPool() {}
  ThreadPool(size_t);
  ThreadPool(size_t threads, bool bBindMajorCpu);
  ThreadPool(size_t threads, unsigned int nCpuID);
  template <class F, class... Args>
  auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
  ~ThreadPool();

  static bool getCpuThreads(unsigned int nID, std::set<int>& threads) {
    std::unique_lock<std::mutex> lock(cpuSetMutex);
    if (nID >= cpuSet.size()) {
      return false;
    }
    threads = cpuSet[nID];
    return true;
  }

 private:
  void run() {
    for (;;) {
      std::function<void()> task;
      {
        std::unique_lock<std::mutex> lock(this->queue_mutex);
        this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
        if (this->stop && this->tasks.empty()) return;
        task = std::move(this->tasks.front());
        this->tasks.pop();
      }
      task();
    }
  }

  void bindMajorCpu() {}

  void bindMinorCpu() {}

  static void bindCpu(unsigned int nID) {}

 private:
  // need to keep track of threads so we can join them
  std::vector<std::thread> workers;
  // the task queue
  std::queue<std::function<void()> > tasks;

  // synchronization
  std::mutex queue_mutex;
  std::condition_variable condition;

  bool stop;
  static std::vector<std::set<int> > cpuSet;
  static std::mutex cpuSetMutex;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads) : stop(false) {
  for (size_t i = 0; i < threads; ++i) workers.emplace_back([this] { run(); });
}

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads, bool bBindMajorCpu) : stop(false) {
  for (size_t i = 0; i < threads; ++i)
    workers.emplace_back([this, bBindMajorCpu, i] {
      if (bBindMajorCpu) {
        // bindMajorCpu();
      } else {
        // bindMinorCpu();
        switch (i % 4) {
          case 0: {
            bindCpu(0);
            break;
          }
          case 1: {
            bindCpu(1);
            break;
          }
          case 2: {
            bindCpu(2);
            break;
          }
          case 3: {
            bindCpu(3);
            break;
          }
          default: {
            break;
          }
        }
      }

      run();
    });
}

inline ThreadPool::ThreadPool(size_t threads, unsigned int nCpuID) : stop(false) {
  for (size_t i = 0; i < threads; ++i)
    workers.emplace_back([this, nCpuID] {
      bindCpu(nCpuID);
      run();
    });
}

// add new work item to the pool
template <class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
  using return_type = typename std::result_of<F(Args...)>::type;

  auto task =
      std::make_shared<std::packaged_task<return_type()> >(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

  std::future<return_type> res = task->get_future();
  {
    std::unique_lock<std::mutex> lock(queue_mutex);

    // don't allow enqueueing after stopping the pool
    if (stop) throw std::runtime_error("enqueue on stopped ThreadPool");

    tasks.emplace([task]() { (*task)(); });
  }
  condition.notify_one();
  return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;
  }
  condition.notify_all();
  for (std::thread& worker : workers) worker.join();
}

#endif  // THREADPOOL_H
