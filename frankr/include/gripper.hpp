/* Copyright (c) 2020, Danish Technological Institute.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 * 
 * Original author: Lars Berscheid <lars.berscheid@kit.edu>
 */

#pragma once

#include <cmath>
#include <iostream>
#include <future>

#include <franka/exception.h>
#include <franka/gripper.h>


class Gripper: franka::Gripper {
  const double width_calibration {0.004}; // [m], Difference from gripper jaws
  const double min_width {0.002}; // [m]

  /**
   * Save clamp width and compare it in the is_grasping method. If it's smaller,
   * the gripper moves and the object is missing.
   */
  double last_clamp_width; // [m]

public:
  /**
   * Connects to a gripper at the given FCI IP address.
   */
  Gripper(const std::string& fci_ip);
  Gripper(const std::string& fci_ip, double gripper_speed, double gripper_force);

  std::string fci_ip;

  double gripper_force {20.0}; // [N]
  double gripper_speed {0.02}; // [m/s]

  const double max_width {0.081 + width_calibration}; // [m]

  double width() const;
  bool homing() const;
  bool stop() const;
  bool isGrasping() const;

  bool move(double width); // [m]
  std::future<bool> moveAsync(double width); // [m]
  bool open();
  bool clamp();
  bool release(double width); // [m]
};
