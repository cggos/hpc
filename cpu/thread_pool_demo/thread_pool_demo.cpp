#include <chrono>
#include <cstddef>
#include <exception>
#include <functional>
#include <future>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <thread>
#include <vector>

#include "hpc/cpu/thread_pool.h"

long long sum_range(const std::vector<int>& values, std::size_t begin, std::size_t end) {
  long long total = 0;
  for (std::size_t i = begin; i < end; ++i) {
    total += static_cast<long long>(values[i]) * values[i];
  }
  return total;
}

int main() {
  const std::size_t worker_count = 4;
  hpc::ThreadPool pool(worker_count);

  std::cout << "workers=" << pool.worker_count() << '\n';

  std::vector<std::future<int>> small_jobs;
  for (int i = 0; i < 8; ++i) {
    small_jobs.push_back(pool.submit([i] {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      return i * i;
    }));
  }

  std::cout << "small job results:";
  for (auto& job : small_jobs) {
    std::cout << ' ' << job.get();
  }
  std::cout << '\n';

  std::vector<int> values(1'000'000);
  std::iota(values.begin(), values.end(), 1);

  const std::size_t shard_size = values.size() / worker_count;
  std::vector<std::future<long long>> shards;
  for (std::size_t worker = 0; worker < worker_count; ++worker) {
    const std::size_t begin = worker * shard_size;
    const std::size_t end = (worker + 1 == worker_count) ? values.size() : begin + shard_size;
    shards.push_back(pool.submit(sum_range, std::cref(values), begin, end));
  }

  long long parallel_total = 0;
  for (auto& shard : shards) {
    parallel_total += shard.get();
  }

  std::cout << "sum of squares=" << parallel_total << '\n';

  auto failing_job = pool.submit([]() -> int { throw std::runtime_error("task exception is stored in future"); });

  try {
    (void)failing_job.get();
  } catch (const std::exception& e) {
    std::cout << "caught task error: " << e.what() << '\n';
  }

  return 0;
}
