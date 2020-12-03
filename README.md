<div align="center">
  <div style="float: left; width: 50%; padding: 5px;">
    <img width="340" src="https://raw.githubusercontent.com/dti-research/frankr/master/resources/franka_emika_logo.png">
  </div>
  <div style="float: left; width: 50%; padding: 5px;">
    <img width="340" src="https://raw.githubusercontent.com/dti-research/frankr/master/resources/ros_logo.png">
  </div>
  <h3 align="center">
    Franka R - High-Level Motion Library for the Franka Panda Robot Using ROS
  </h3>
</div>

Frankr is a high-level C++ and Python API for controlling the Franka Emika Panda Robot through ROS. We are using our own fork of MoveIt and the `panda_moveit_config` package to control the robot as the default kinetic-devel branch in `panda_moveit_config` contains wrong information about collisions for the robot. Therefore we're building all packages from source, see the [Dockerfile](docker/Dockerfile) for more details on the installation. 

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

## Acknowledgements

Frankr is originally authored by [@pantor](https://github.com/pantor) from which this standalone package is build.

## Versions

Currently, frankr is tested against:

1. ROS Kinetic
1. libfranka 0.8.0
1. Panda controller firmware 4.0.4

