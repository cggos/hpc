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

#include <Eigen/Core>
#include <limits>

namespace hpc {

#ifndef _MSC_VER
#include <stdint.h>
#else
typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#endif

#define DELETE_NEW_OBJ(obj) \
  if (nullptr != obj) {     \
    delete obj;             \
    obj = nullptr;          \
  }

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

template <class Scalar, int M>
using TVec = Eigen::Matrix<Scalar, M, 1>;

template <class Scalar, int M, int N>
using TMat = Eigen::Matrix<Scalar, M, N>;

template <int M>
using TVecf = TVec<TScalarF, M>;

template <int M>
using TVeci = TVec<TScalarI, M>;

template <int M, int N>
using TMatf = TMat<TScalarF, M, N>;

template <int M, int N>
using TMati = TMat<TScalarI, M, N>;

using TVec2f = TVecf<2>;
using TVec3f = TVecf<3>;
using TVec4f = TVecf<4>;
using TVec5f = TVecf<5>;
using TVec6f = TVecf<6>;
using TVec7f = TVecf<7>;
using TVec8f = TVecf<8>;

using TVec2i = TVeci<2>;
using TVec3i = TVeci<3>;
using TVec4i = TVeci<4>;
using TVec6i = TVeci<6>;
using TVec7i = TVeci<7>;
using TVec8i = TVeci<8>;

using TMat2f = TMatf<2, 2>;
using TMat3f = TMatf<3, 3>;
using TMat4f = TMatf<4, 4>;
using TMat6f = TMatf<6, 6>;

using TMat2i = TMati<2, 2>;
using TMat3i = TMati<3, 3>;
using TMat4i = TMati<4, 4>;
using TMat6i = TMati<6, 6>;

using TVecXf = TVecf<Eigen::Dynamic>;
using TMatXf = TMatf<Eigen::Dynamic, Eigen::Dynamic>;

using TVecXi = TVeci<Eigen::Dynamic>;
using TMatXi = TMati<Eigen::Dynamic, Eigen::Dynamic>;

using TVec3FP64 = TVec<double, 3>;

template <int M>
using TMatDf = Eigen::DiagonalMatrix<TScalarF, M>;

using TMatD3f = TMatDf<3>;
using TMatD6f = TMatDf<6>;

}  // namespace hpc