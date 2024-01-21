#!/bin/bash
#Drone_1
sim_vehicle.py -v ArduCopter -f gazebo-iris --console --map -I0 --out=tcpin=0.0.0.0:8100
#Drone_2
sim_vehicle.py -v ArduCopter -f gazebo-iris --console --map -I1 --out=tcpin=0.0.0.0:8200
#Drone_3
sim_vehicle.py -v ArduCopter -f gazebo-iris --console --map -I2 --out=tcpin=0.0.0.0:8200
#U need wait until the EKF start use GPS