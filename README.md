# Fritzrobot_control

## Description
robot's control pkgs.
##
### 2023-12-28 update
added odom_fuser, which takes ekf estimated orientation as yaw, synchornizing the /imu(50 hz) with chassis/vel(200hz)
added odom_publisher, forked from official tutorial, which solve the pose only on encoder's data.
### 2023-12-26 update
added odometry in gazebo through the service "get_model_state" 
### 2023-11-14 update
https://user-images.githubusercontent.com/33782458/282789273-b32c4797-414c-4ea5-ad79-b59723b437a7.mp4
### 2023-11-03 update
Added joy-stick control node, which extended the joy-stick control with transverse movement. 

[`xone`](https://github.com/medusalix/xone) needs to be installed to enable the xbox wireless adapter on ubuntu.


And two packages needed to be installed in advance.
```
sudo apt-get install ros-noetic-teleop-twist-joy
sudo apt-get install ros-noetic-joy
```
