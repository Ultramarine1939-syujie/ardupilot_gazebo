#运行后在文件夹会生成载具参数文件
#启动SITL
#cd ~/repos/ardupilot/ArduCopter/ & sim_vehicle.py -v ArduCopter -f gazebo-iris --console --map & sleep 5;
#启动gazebo
roslaunch apm_sim iris_d435.launch & sleep 5;

#启动mavros
roslaunch mavros apm.launch fcu_url:=udp://127.0.0.1:14550@ & sleep 5;
#调整IMU频率
rosrun mavros mavcmd long 511 26 5000 0 0 0 0 0	& sleep 2;	#data_raw   200Hz
rosrun mavros mavcmd long 511 31 5000 0 0 0 0 0	& sleep 2;	#data   200Hz

#启动VINS（测试文件，不建议使用）
roslaunch vins fast_drone_250.launch & sleep 5;
roslaunch ego_planner rviz.launch & sleep 5;
roslaunch ego_planner single_run_in_exp.launch ;
wait;
# roslaunch vins vins_rviz.launch & sleep 3
# rosrun vins vins_node /home/ubuntu/repos/VINS-Fusion/src/VINS-Fusion/config/ardupilot_gazebo/ardupilot_sitl_stereo_imu_config.yaml
wait;
