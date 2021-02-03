/* Copyright (c) 2020, Danish Technological Institute.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 * 
 * Original author: Lars Berscheid <lars.berscheid@kit.edu>
 */

#pragma once

#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <moveit/trajectory_processing/iterative_time_parameterization.h>

#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <geometry_msgs/WrenchStamped.h>
#include <franka_msgs/FrankaState.h>
#include <franka_msgs/ErrorRecoveryAction.h>
#include <franka_msgs/ErrorRecoveryActionGoal.h>
#include <franka_msgs/ErrorRecoveryGoal.h>

#include <geometry.hpp>
#include <motion.hpp>
#include <waypoint.hpp>


class RosNode {
public:
  RosNode() {
    int argc = 0;
    ros::init(argc, NULL, "cfrankr");
  }
};


class Robot: RosNode, moveit::planning_interface::MoveGroupInterface {
  ros::NodeHandle node_handle;
  ros::Subscriber sub_wrench;
  ros::Subscriber sub_states;
  ros::AsyncSpinner spinner {2};

  moveit::planning_interface::MoveGroupInterface::Plan my_plan;

  std::shared_ptr<MotionData> current_motion_data;

  std::mutex mutex;
  std::condition_variable wait_condition_variable;
  bool flag {false};

  template<typename T>
  auto restartMoveItIfCommandFails(T lambda, long int timeout) {
    auto future = std::async(std::launch::async, lambda);
    auto status = future.wait_for(std::chrono::seconds(timeout));

    while (status == std::future_status::timeout) {
      restartMoveIt();

      future = std::async(std::launch::async, lambda);
      status = future.wait_for(std::chrono::seconds(timeout));
    }
    return future.get();
  }

  actionlib::SimpleActionClient<franka_msgs::ErrorRecoveryAction> ac{"franka_control/error_recovery", true};
  
  void stateCallback(const franka_msgs::FrankaState& msg);
  void wrenchCallback(const geometry_msgs::WrenchStamped& msg);

public:
  franka_msgs::FrankaState::_robot_mode_type robot_mode;
  // Break conditions
  bool is_moving {false};
  bool has_reflex_error {(this->robot_mode == franka_msgs::FrankaState::ROBOT_MODE_REFLEX)};

  double velocity_rel {1.0};
  double acceleration_rel {1.0};

  Robot(const std::string &name);
  Robot(const std::string &name, double dynamic_rel);

  Affine currentPose(const Affine& frame);

  int restartMoveIt();
  bool recoverFromErrors();

  bool moveJoints(const std::array<double, 7>& joint_values, MotionData& data);

  bool movePtp(const Affine& frame, const Affine& affine, MotionData& data);
  bool moveRelativePtp(const Affine& frame, const Affine& affine, MotionData& data);
  bool moveWaypointsPtp(const Affine& frame, const std::vector<Waypoint>& waypoints, MotionData& data);

  bool moveCartesian(const Affine& frame, const Affine& affine, MotionData& data);
  bool moveRelativeCartesian(const Affine& frame, const Affine& affine, MotionData& data);
  bool moveWaypointsCartesian(const Affine& frame, const std::vector<Waypoint>& waypoints, MotionData& data);
};
