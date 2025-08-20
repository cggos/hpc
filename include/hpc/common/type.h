/**
 * @file type.h
 * @author Gavin Gao (cggos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2025-08-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <math.h>

#include <limits>

namespace hpc {

// EPSILON
constexpr float kEPS = 1e-5;
const float kEPS_FLT = std::numeric_limits<float>::epsilon();
const double kEPS_DBL = std::numeric_limits<double>::epsilon();

// Max
constexpr float kMAX_FLT = std::numeric_limits<float>::max();

// Radian & Degree
constexpr float kRAD2DEG = 180.f * M_1_PI;
constexpr float kDEG2RAD = M_PI / 180.f;

// single- or double-precision floating-point format scalar
using TScalarF = double;
using TScalarI = int;

}  // namespace hpc