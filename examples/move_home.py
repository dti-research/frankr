from argparse import ArgumentParser

from cfrankr import Robot, Gripper, Affine, MotionData

if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('--host', default='panda_arm', help='name of the robot')
    args = parser.parse_args()

    # Setup Robot
    general_dynamics_rel = 0.32
    robot = Robot(args.host, general_dynamics_rel)
    robot.recover_from_errors()

    # Move down
    md_home = MotionData().with_dynamics(0.3)
    robot.move_joints([-1.811944, 1.179108, 1.757100, -2.14162, -1.143369, 1.633046, -0.432171], md_home)