/**
 * @file cpu.cpp
 * @author Gavin Gao (cggos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-04-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hpc/cpu/cpu.h"

#include <sstream>

namespace hpc {

std::string CPU::processor_arch() {
  std::string str_arch = "x86-64";
#if defined(__arm__) || defined(__aarch64__)
  str_arch = "aarch64";
#elif defined __x86_64__
  str_arch = "x86-64";
#endif
  return str_arch;
}

unsigned int CPU::processor_num() {
  // std::thread::hardware_concurrency();
  return sysconf(_SC_NPROCESSORS_CONF);  // _SC_NPROCESSORS_CONF的值为CPU个数，基于0开始编号
}

std::thread::id CPU::get_thread_id(const std::thread& t) { return t.get_id(); }

void CPU::set_thread_name(pthread_t th, const std::string& str_thread_name) {
  pthread_setname_np(th, str_thread_name.c_str());
}

void CPU::set_current_thread_name(const std::string& str_thread_name) {
  pthread_setname_np(pthread_self(), str_thread_name.c_str());
}

std::string CPU::get_thread_name(pthread_t th) {
  char th_name[16] = {0};
  pthread_getname_np(th, th_name, 16);
  return std::string(th_name);
}

std::string CPU::get_current_thread_name() { return get_thread_name(pthread_self()); }

void CPU::print_current_thread_info() {
  std::stringstream ss;
  auto cpu_ids = get_current_thread_affinity();
  for (auto id : cpu_ids) ss << id;
  printf("\t current thread (%s)\t is running at cpu(%s)", get_current_thread_name().c_str(), ss.str().c_str());
}

// void set_current_thread_affinity_mask(int mask, pid_t pid) {
//   int err;
//   int syscallres = syscall(__NR_sched_setaffinity, pid, sizeof(mask), &mask);
//   if (syscallres) {
//     // err = errno;
//     // LOGE("Error in the syscall setaffinity: mask=%d=0x%x err=%d=0x%x", mask, mask, err, err);
//   }
// }

bool CPU::set_thread_affinity(pthread_t th, const std::vector<unsigned int>& cpu_ids) {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  for (const auto& id : cpu_ids) CPU_SET(id, &cpuset);
  int ret = pthread_setaffinity_np(th, sizeof(cpuset), &cpuset);
  return ret >= 0;
  // setCurrentThreadAffinityMask(th, (int)cpuset.__bits);
  // sched_setaffinity(th, sizeof(cpuset), &cpuset);
  // return true;
}

bool CPU::set_current_process_affinity(const std::vector<unsigned int>& cpu_ids) {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  for (auto& iter : cpu_ids) CPU_SET(iter, &cpuset);

  // 将指定进程ID绑定到CPU, 0代表当前进程
  int ret = sched_setaffinity(0, sizeof(cpuset), &cpuset);
  return ret >= 0;
}

std::vector<unsigned int> CPU::get_thread_affinity(pthread_t th) {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  int ret = pthread_getaffinity_np(th, sizeof(cpuset), &cpuset);
  // int ret = sched_getaffinity(th, sizeof(cpuset), &cpuset);
  if (ret < 0) return {};

  std::vector<unsigned int> cpu_ids;
  for (unsigned int i = 0; i < processor_num(); ++i)
    if (CPU_ISSET(i, &cpuset)) cpu_ids.push_back(i);

  return cpu_ids;
}

std::vector<unsigned int> CPU::get_current_thread_affinity() { return get_thread_affinity(pthread_self()); }

std::vector<unsigned int> CPU::get_current_process_affinity() {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  int ret = sched_getaffinity(0, sizeof(cpuset), &cpuset);
  if (ret < 0) return {};

  std::vector<unsigned int> cpu_ids;
  for (unsigned int i = 0; i < processor_num(); ++i)
    if (CPU_ISSET(i, &cpuset)) cpu_ids.push_back(i);

  return cpu_ids;
}

void CPU::tfunc(const std::string& str_thread_name, std::function<void()> func, int period_std_ms) {
  set_current_thread_name(str_thread_name);

  const int kPeriodStd = period_std_ms;  // ms
  while (true) {
    auto t0 = std::chrono::system_clock::now();

    print_current_thread_info();

    func();

    auto t1 = std::chrono::system_clock::now();
    auto period01 = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

    if (period01 < kPeriodStd) std::this_thread::sleep_for(std::chrono::milliseconds(kPeriodStd - period01));

    auto t2 = std::chrono::system_clock::now();
    auto period02 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t0).count();

    printf("(%s)\t period01 %d ms, period02 %d ms", str_thread_name.c_str(), period01, period02);
  }
}

}  // namespace hpc