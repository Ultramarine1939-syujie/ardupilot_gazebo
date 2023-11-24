#!/bin/bash

# 启动第一个进程
roslaunch apm_sim iris_runway.launch &
sleep 5

# 启动第二个进程
cd ~/ardupilot/ArduCopter/
sim_vehicle.py -v ArduCopter -f gazebo-iris --console &
sleep 5

# 启动第三个进程
roslaunch mavros apm.launch fcu_url:=udp://127.0.0.1:14550@14550  #14855换成仿真输出端口

# 等待所有进程完成
wait
