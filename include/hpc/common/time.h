/**
 * @file time.h
 * @author Gavin Gao (cggos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <chrono>

#include "vp_base/common/log.h"

namespace vpb {

class TicToc {
 public:
  TicToc() { tic(); }

  /**
   * @brief
   *
   * @return double unit: ms
   */
  double toc() {
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    return elapsed_seconds.count() * 1e3;
  }

 private:
  std::chrono::time_point<std::chrono::steady_clock> start, end;

  void tic() { start = std::chrono::steady_clock::now(); }
};

class Time {
 public:
  static std::chrono::milliseconds system_now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  }

  static std::chrono::milliseconds steady_now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch());
  }

  static double to_seconds(const std::chrono::milliseconds &duration) {
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
  }

  static double to_seconds(const std::chrono::steady_clock::duration &duration) {
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
  }

  static double sys_diff_time() { return to_seconds(system_now() - steady_now()); }

  static bool check_timestamp(double ts, vpb::Log::Ptr logger_ptr = nullptr) {
    std::int64_t sec64 = static_cast<std::int64_t>(std::floor(ts));
    if (sec64 < 0 || sec64 > std::numeric_limits<std::uint32_t>::max()) {
      if (logger_ptr) SPDLOG_LOGGER_WARN(logger_ptr, "Time is out of dual 32-bit range");
      return false;
    }
    return true;
  }

  /**
   * @brief Second --> [Sec, NSec]
   * @ref fromSec in ROS
   * @param t
   * @param sec
   * @param nsec
   */
  static void from_sec(double t, uint32_t &sec, uint32_t &nsec) {
    int64_t sec64 = static_cast<int64_t>(floor(t));
    if (sec64 < 0 || sec64 > std::numeric_limits<uint32_t>::max())
      throw std::runtime_error("Time is out of dual 32-bit range");
    sec = static_cast<uint32_t>(sec64);
    nsec = static_cast<uint32_t>(std::round((t - sec) * 1e9));
    // avoid rounding errors
    sec += (nsec / 1000000000ul);
    nsec %= 1000000000ul;
  }

  void tp_mark() { vec_tps_.emplace_back(std::chrono::system_clock::now()); };

  friend void operator<<(Log::Ptr logger_ptr, const Time &time);

 private:
  std::vector<std::chrono::system_clock::time_point> vec_tps_;
};

// void operator<<(Log::Ptr logger_ptr, const Time &time) {
//   const auto &tps = time.vec_tps_;
//   if (tps.size() > 2) {
//     SPDLOG_LOGGER_INFO(logger_ptr, "time benchmark");
//     for (int i = 1; i < tps.size(); i++) {
//       auto &&tij = std::chrono::duration_cast<std::chrono::microseconds>(tps[i] - tps[i - 1]).count() * 1e-3;
//       SPDLOG_LOGGER_INFO(logger_ptr, "\t t{}{}(ms) {}", i - 1, i, tij);
//     }
//   }
// }

}  // namespace vpb
