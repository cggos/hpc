/**
 * @file io_yaml.h
 * @author Gavin Gao (cggos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2021-07-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <yaml-cpp/yaml.h>

#include <Eigen/Geometry>

#include "hpc/common/type.h"

/**
 * @brief
 * @ref https://github.com/jbeder/yaml-cpp/wiki/Tutorial
 *
 */
namespace YAML {

// Vector2f
template <>
struct convert<hpc::TVec2f> {
  static bool decode(const Node& node, hpc::TVec2f& rhs) {
    if (!node.IsSequence() || node.size() != 2) {
      return false;
    }
    rhs[0] = node[0].as<hpc::TScalarF>();
    rhs[1] = node[1].as<hpc::TScalarF>();
    return true;
  }
};

// Vector3f
template <>
struct convert<hpc::TVec3f> {
  static bool decode(const Node& node, hpc::TVec3f& rhs) {
    if (!node.IsSequence() || node.size() != 3) {
      return false;
    }
    rhs[0] = node[0].as<hpc::TScalarF>();
    rhs[1] = node[1].as<hpc::TScalarF>();
    rhs[2] = node[2].as<hpc::TScalarF>();
    return true;
  }
};

// Vector4f
template <>
struct convert<hpc::TVec4f> {
  static Node encode(const hpc::TVec4f& rhs) {
    Node node;
    node.push_back(rhs[0]);
    node.push_back(rhs[1]);
    node.push_back(rhs[2]);
    node.push_back(rhs[3]);
    return node;
  }

  static bool decode(const Node& node, hpc::TVec4f& rhs) {
    if (!node.IsSequence() || node.size() != 4) {
      return false;
    }
    rhs[0] = node[0].as<hpc::TScalarF>();
    rhs[1] = node[1].as<hpc::TScalarF>();
    rhs[2] = node[2].as<hpc::TScalarF>();
    rhs[3] = node[3].as<hpc::TScalarF>();
    return true;
  }
};

// Matrix4f
template <>
struct convert<hpc::TMat4f> {
  static bool decode(const Node& node, hpc::TMat4f& rhs) {
    if (!node.IsSequence() || node.size() != 16) {
      return false;
    }

    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j) rhs(i, j) = node[j + i * 4].as<hpc::TScalarF>();

    return true;
  }
};

// VectorXf
template <>
struct convert<hpc::TVecXf> {
  static bool decode(const Node& node, hpc::TVecXf& rhs) {
    int sz = node.size();
    if (!node.IsSequence() || sz <= 0) return false;
    rhs.resize(sz);
    for (int i = 0; i < node.size(); i++) rhs[i] = node[i].as<hpc::TScalarF>();
    return true;
  }
};

template <>
struct convert<std::vector<hpc::TScalarF>> {
  static bool decode(const Node& node, std::vector<hpc::TScalarF>& rhs) {
    int sz = node.size();
    if (!node.IsSequence() || sz <= 0) return false;
    rhs.resize(sz);
    for (int i = 0; i < node.size(); i++) rhs[i] = node[i].as<hpc::TScalarF>();
    return true;
  }
};

}  // namespace YAML
