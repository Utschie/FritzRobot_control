# Fritzrobot_control

## Description
robot's control pkgs.
##
### 2024-01-07 update
add rgbd camera node, the camera's driving pkg [`astra_camera`](https://github.com/orbbec/ros_astra_camera) is supplied by the manufacturer. 
### 2023-12-31 update
odom published with odom_fuser, and visible in rviz. The model's and map's descriptions are in [`FritzRobot_description`](https://github.com/Utschie/FritzRobot_description)

https://private-user-images.githubusercontent.com/33782458/293521114-47dbf14f-da07-41da-9ce6-780ed813ba5d.mp4
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
