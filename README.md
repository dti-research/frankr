<div align="center">
  <div style="float: left; width: 45%; padding: 5px;">
    <img width="340" src="https://raw.githubusercontent.com/dti-research/frankr/master/resources/franka_emika_logo.png">
  </div>
  <div style="float: left; width: 45%; padding: 5px;">
    <img width="200" src="https://raw.githubusercontent.com/dti-research/frankr/master/resources/ros_logo.png">
  </div>
  <h3 align="center">
    Franka R - High-Level Motion Library for the Franka Panda Robot Using ROS
  </h3>
</div>

Frankr is a high-level C++ and Python API for controlling the Franka Emika Panda Robot through ROS. We are using our own fork of the `panda_moveit_config` package to control the robot as the default kinetic-devel branch in `panda_moveit_config` contains wrong information about collisions for the robot. See the [Dockerfile](docker/Dockerfile) for more details on the installation. 

## Usage

For manual build of the docker image see: [INSTALL.md](INSTALL.md)

Pull the docker image:

```
docker pull dtiresearch/frankr
```

Run the container:

```
docker run -it --rm --network=host --privileged \
    -v $(pwd):/home/workspace/test \
    -w /home/workspace/ \
    dtiresearch/frankr
```

## Running the Examples

Open two more terminals and connect them to the running Docker container by `docker exec -it ... bash`. Then launch the following launch files in these terminals 

```
roslaunch franka_control franka_control robot_ip:=172.16.0.2
roslaunch panda_moveit_config panda_moveit.launch
```

Now you're ready to test out the examples on your system. Always have a user ready at the emergency stop when moving the (any) robot! Simply run:

```
python3 examples/gripper.py --host 172.16.0.2
...
python3 examples/home.py
```

## Acknowledgements

Frankr is originally authored by Lars Berscheid from KIT [@pantor](https://github.com/pantor) from which this standalone package is build.

## Versions

Currently, frankr is tested against:

1. ROS Kinetic
1. libfranka 0.8.0
1. Panda controller firmware 4.0.4

