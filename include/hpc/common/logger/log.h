/**
 * @file log.h
 * @author Gavin Gao (cggos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2025-08-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

namespace hpc {

#ifdef __USER_DEBUG__
#if __cplusplus < 201103L
#define DEBUG_LOG(format, ...) printf("File: %s, Line: %05d: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_LOG(format, ...) printf("File: %s, Line: %05d: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif
#else
#define DEBUG_LOG(format, ...)
#endif

#define endll std::endl << std::endl  // double end line definition

}  // namespace hpc