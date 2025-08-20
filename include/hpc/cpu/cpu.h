/**
 * @file cpu.h
 * @author Gavin Gao (cggos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <opencv2/core/utility.hpp>
#include <string>
#include <thread>
#include <vector>

// #include "vp_base/common/log.h"

namespace hpc {

class CPU {
 public:
  CPU() = delete;

  CPU(const CPU&) = delete;

  using Ptr = std::shared_ptr<CPU>;

  static std::string processor_arch();

  static unsigned int processor_num();

  static std::thread::id get_thread_id(const std::thread& t);

  static void set_thread_name(pthread_t th, const std::string& str_thread_name);

  static std::string get_thread_name(pthread_t th);

  static void set_current_thread_name(const std::string& str_thread_name);

  static std::string get_current_thread_name();

  static void print_current_thread_info();

  static bool set_thread_affinity(pthread_t th, const std::vector<unsigned int>& cpu_ids);

  static std::vector<unsigned int> get_thread_affinity(pthread_t th);

  static bool set_current_process_affinity(const std::vector<unsigned int>& cpu_ids);

  static std::vector<unsigned int> get_current_thread_affinity();

  static std::vector<unsigned int> get_current_process_affinity();

  void tfunc(const std::string& str_thread_name, std::function<void()> func, int period_std_ms);
};

/*
 * @brief Helper class to do OpenCV parallelization
 *
 * This is a utility class required to build with older version of opencv
 * On newer versions this doesn't seem to be needed, but here we just use it to ensure we can work for more opencv
 * version.
 * https://answers.opencv.org/question/65800/how-to-use-lambda-as-a-parameter-to-parallel_for_/?answer=130691#post-id-130691
 */
class LambdaBodyParallel : public cv::ParallelLoopBody {
 public:
  explicit LambdaBodyParallel(const std::function<void(const cv::Range&)>& body) { _body = body; }
  void operator()(const cv::Range& range) const override { _body(range); }

 private:
  std::function<void(const cv::Range&)> _body;
};

}  // namespace hpc
