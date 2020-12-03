from argparse import ArgumentParser

from cfrankr import Gripper

if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('--host', default='172.16.0.2', help='FCI IP of the robot')
    args = parser.parse_args()

    # Setup Gripper
    gripper = Gripper()

    # Homing
    gripper.homing()

    print("Gripper max width: " + gripper.max_width + " [m]")

    # Clamp
    gripper.clamp()

    # Open
    gripper.open()