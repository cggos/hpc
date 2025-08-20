/**
 * @file yaml_io.h
 * @author Gavin Gao (cggos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2021-07-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef IO_YAML_H
#define IO_YAML_H

#include <yaml-cpp/yaml.h>

#include <Eigen/Geometry>

#include "vp_base/common/type.h"

/**
 * @brief
 * @ref https://github.com/jbeder/yaml-cpp/wiki/Tutorial
 *
 */
namespace YAML {

// Vector2f
template <>
struct convert<vpb::TVec2f> {
  static bool decode(const Node& node, vpb::TVec2f& rhs) {
    if (!node.IsSequence() || node.size() != 2) {
      return false;
    }
    rhs[0] = node[0].as<vpb::TScalarF>();
    rhs[1] = node[1].as<vpb::TScalarF>();
    return true;
  }
};

// Vector3f
template <>
struct convert<vpb::TVec3f> {
  static bool decode(const Node& node, vpb::TVec3f& rhs) {
    if (!node.IsSequence() || node.size() != 3) {
      return false;
    }
    rhs[0] = node[0].as<vpb::TScalarF>();
    rhs[1] = node[1].as<vpb::TScalarF>();
    rhs[2] = node[2].as<vpb::TScalarF>();
    return true;
  }
};

// Vector4f
template <>
struct convert<vpb::TVec4f> {
  static Node encode(const vpb::TVec4f& rhs) {
    Node node;
    node.push_back(rhs[0]);
    node.push_back(rhs[1]);
    node.push_back(rhs[2]);
    node.push_back(rhs[3]);
    return node;
  }

  static bool decode(const Node& node, vpb::TVec4f& rhs) {
    if (!node.IsSequence() || node.size() != 4) {
      return false;
    }
    rhs[0] = node[0].as<vpb::TScalarF>();
    rhs[1] = node[1].as<vpb::TScalarF>();
    rhs[2] = node[2].as<vpb::TScalarF>();
    rhs[3] = node[3].as<vpb::TScalarF>();
    return true;
  }
};

// Matrix4f
template <>
struct convert<vpb::TMat4f> {
  static bool decode(const Node& node, vpb::TMat4f& rhs) {
    if (!node.IsSequence() || node.size() != 16) {
      return false;
    }

    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j) rhs(i, j) = node[j + i * 4].as<vpb::TScalarF>();

    return true;
  }
};

// VectorXf
template <>
struct convert<vpb::TVecXf> {
  static bool decode(const Node& node, vpb::TVecXf& rhs) {
    int sz = node.size();
    if (!node.IsSequence() || sz <= 0) return false;
    rhs.resize(sz);
    for (int i = 0; i < node.size(); i++) rhs[i] = node[i].as<vpb::TScalarF>();
    return true;
  }
};

template <>
struct convert<std::vector<vpb::TScalarF>> {
  static bool decode(const Node& node, std::vector<vpb::TScalarF>& rhs) {
    int sz = node.size();
    if (!node.IsSequence() || sz <= 0) return false;
    rhs.resize(sz);
    for (int i = 0; i < node.size(); i++) rhs[i] = node[i].as<vpb::TScalarF>();
    return true;
  }
};

}  // namespace YAML

#endif  // IO_YAML_H