# Franka ROS (frankr)

Frankr is a high-level C++ and Python API for controlling the Franka Emika Panda Robot through ROS. We are using our own fork of MoveIt and the `panda_moveit_config` package to control the robot as the default kinetic-devel branch in `panda_moveit_config` contains wrong information about collisions for the robot. Therefore we're building all packages from source, see the [Dockerfile](docker/Dockerfile) for more details on the installation. 

## Usage

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

Frankr is originally authored by [@pantor](https://github.com/pantor) from which this package is build.

## Versions

Currently, frankr is tested against:

1. ROS Kinetic
1. libfranka 0.8.0
1. Panda controller firmware 4.0.4

