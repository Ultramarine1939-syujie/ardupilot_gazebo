# The installation of Cartographer

https://google-cartographer-ros.readthedocs.io/en/latest/configuration.html#lua-configuration-reference-documentation

## Building & Installation

In order to build Cartographer ROS, we recommend using [wstool](http://wiki.ros.org/wstool) and [rosdep](http://wiki.ros.org/rosdep). For faster builds, we also recommend using [Ninja](https://ninja-build.org/).

On Ubuntu Focal with ROS Noetic use these commands to install the above tools:

```
sudo apt-get update
sudo apt-get install -y python3-wstool python3-rosdep ninja-build stow
```

On older distributions:

```
sudo apt-get update
sudo apt-get install -y python-wstool python-rosdep ninja-build stow
```

After the tools are installed, create a new cartographer_ros workspace in ‘catkin_ws’.

```
mkdir catkin_ws
cd catkin_ws
wstool init src
wstool merge -t src https://raw.githubusercontent.com/cartographer-project/cartographer_ros/master/cartographer_ros.rosinstall
wstool update -t src
```

Now you need to install cartographer_ros’ dependencies. First, we use `rosdep` to install the required packages. The command ‘sudo rosdep init’ will print an error if you have already executed it since installing ROS. This error can be ignored.

```
sudo rosdep init
rosdep update
rosdep install --from-paths src --ignore-src --rosdistro=${ROS_DISTRO} -y
```

Cartographer uses the [abseil-cpp](https://abseil.io/) library that needs to be manually installed using this script:

```
src/cartographer/scripts/install_abseil.sh
src/cartographer/scripts/install_proto3.sh
```

Due to conflicting versions you might need to uninstall the ROS abseil-cpp using

```
sudo apt-get remove ros-${ROS_DISTRO}-abseil-cpp
```

Build and install.

```
catkin_make_isolated --install --use-ninja
```

This builds Cartographer from the latest HEAD of the master branch. If you want a specific version, you need to change the version in the cartographer_ros.rosinstall.

## Attention

> Well, as it turns out that this dependency was added to the cartographer package roughly a week ago (as can be seen here [https://github.com/cartographer-project/cartographer/pull/1875](https://github.com/cartographer-project/cartographer_ros/issues/url)); removing the respective line from the package.xml and installing abseil via the command from the guide (ie. `src/cartographer/scripts/install_abseil.sh`) seems to have fixed the issue, atleast in so far as it allowed me to build and install cartographer ros.

```shell
ERROR: the following packages/stacks could not have their rosdep keys resolved to system dependencies: cartographer: [libabsl-dev] defined as "not available" for OS version [focal] 
```

### The version of software

Here are some problems I met.

```
pip install Sphinx==1.7.9
pip install Jinja2==2.10
Eigen == 3.3.7
sudo apt-get install ros-noetic-pcl-conversions
```

`google_carto_ws/src/.rosinstall`

```
- git:
    local-name: cartographer
    uri: https://github.com/googlecartographer/cartographer.git
- git:
    local-name: cartographer_ros
    uri: https://github.com/googlecartographer/cartographer_ros.git
- git:
    local-name: ceres-solver
    uri: https://github.com/ceres-solver/ceres-solver.git
    version: 1.12.0rc4
- git:
    local-name: cartographer_turtlebot
    uri: https://github.com/googlecartographer/cartographer_turtlebot.git   
- git:
    local-name: cartographer_fetch
    uri: https://github.com/googlecartographer/cartographer_fetch.git  

```

`google_carto_ws/src/cartographter_ros/cartographter_ros.rosinstall `

```
- git: {local-name: cartographer, uri: 'https://github.com/googlecartographer/cartographer.git'}
- git: {local-name: cartographer_ros, uri: 'https://github.com/googlecartographer/cartographer_ros.git'}
- git: {local-name: ceres-solver, uri: 'https://ceres-solver.googlesource.com/ceres-solver.git', version: '1.12.0rc4'}
- git: {local-name: cartographer_turtlebot, uri: 'https://github.com/googlecartographer/cartographer_turtlebot.git'}
- git: {local-name: cartographer_fetch, uri: 'https://github.com/googlecartographer/cartographer_fetch.git'}

```

