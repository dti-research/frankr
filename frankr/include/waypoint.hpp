/* Copyright (c) 2020, Danish Technological Institute.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 * 
 * Original author: Lars Berscheid <lars.berscheid@kit.edu>
 */

#pragma once

#include <geometry.hpp>


struct Waypoint {
  enum class ReferenceType {
    ABSOLUTE,
    RELATIVE
  };

  Affine target_affine;

  ReferenceType reference_type {ReferenceType::ABSOLUTE};

  Waypoint(Affine target_affine): target_affine(target_affine) { }
  Waypoint(Affine target_affine, ReferenceType reference_type): target_affine(target_affine), reference_type(reference_type) { }
};
