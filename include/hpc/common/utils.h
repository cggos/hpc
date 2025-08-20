/**
 * @file utils.h
 * @author Gavin Gao (cggos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-04-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <assert.h>

#include <cmath>
#include <string>

namespace hpc {

class Utils {
 public:
  inline static std::string system_type() {
    std::string str_sys = "linux";
#if defined __linux__
    str_sys = "linux";
#elif defined __ANDROID__
    str_sys = "android";
#endif
    return str_sys;
  }

  static inline void set_env(const std::string &str_env, const std::string &str_env_val) {
    setenv(str_env.c_str(), str_env_val.c_str(), 1);
  }

  static inline std::string get_env(const std::string &str_env) {
    std::string str_env_val;
    char *env_val = std::getenv(str_env.c_str());
    if (env_val != nullptr) str_env_val = env_val;
    return str_env_val;
  }

  /**
   * @brief expand user HOME ("~") directory
   *
   * @ref https://stackoverflow.com/questions/4891006/how-to-create-a-folder-in-the-home-directory
   *
   * @param path sample: "~/.local"
   * @return std::string
   */
  static inline std::string expand_user(std::string path) {
    if (not path.empty() and path[0] == '~') {
      assert(path.size() == 1 or path[1] == '/');  // or other error handling
      char const *home = getenv("HOME");
      if (home or ((home = getenv("USERPROFILE")))) {
        path.replace(0, 1, home);
      } else {
        char const *hdrive = getenv("HOMEDRIVE"), *hpath = getenv("HOMEPATH");
        assert(hdrive);  // or other error handling
        assert(hpath);
        path.replace(0, 1, std::string(hdrive) + hpath);
      }
    }
    return path;
  }

  /**
   * @brief compare float values
   *
   * @param a
   * @param b
   * @param epsilon
   * @return true
   * @return false
   */
  inline static bool cmpf(const double &a, const double &b,
                          const float epsilon = std::numeric_limits<float>::epsilon()) {
    return (std::fabs(a - b) < epsilon);
  }

  /**
   * @brief check for if a floating point number is equal to zero
   *
   * @param a
   * @return true
   * @return false
   */
  inline static bool is_zero(const double &a) { return cmpf(a, 0.f); }
};

}  // namespace hpc
