from argparse import ArgumentParser

from cfrankr import Robot, Gripper, Affine, MotionData

if __name__ == '__main__':
    parser.add_argument('--host', default='panda_arm', help='name of the robot')
    args = parser.parse_args()

    # Setup Robot
    general_dynamics_rel = 0.32
    robot = Robot(args.host, general_dynamics_rel)
    robot.recover_from_errors()

    # Move down
    md_approach_down = MotionData().with_dynamics(0.3).with_z_force_condition(7.0)  # dynamtics is both velocity and acceleration of robot (= 0.3)
    tcp = Affine(0.0, 0.0, 0.18, -np.pi / 4, 0.0, -np.pi)
    approach_distance_from_pose = 0.120
    action_approch_affine = Affine(z = approach_distance_from_pose)
    robot.move_relative_cartesian(tcp, action_approch_affine.inverse(), md_approach_down)
