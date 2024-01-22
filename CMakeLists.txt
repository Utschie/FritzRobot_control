cmake_minimum_required(VERSION 3.0.2)
project(fritzrobot_control)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  nav_msgs
  tf
)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs nav_msgs tf

)


include_directories(
  ${catkin_INCLUDE_DIRS}
  include/${PROJECT_NAME}/
)

add_executable(joy_ext src/joy/joy_ext.cpp)
target_link_libraries(joy_ext ${catkin_LIBRARIES})

add_executable(odom_fuser src/nav/odom_fuser.cpp)
if(nav_msgs_EXPORTED_TARGETS)
  add_dependencies(odom_fuser ${nav_msgs_EXPORTED_TARGETS})
endif()
target_link_libraries(odom_fuser ${catkin_LIBRARIES})

add_executable(gazebo_odometry src/nav/gazebo_odometry.cpp)
target_link_libraries(gazebo_odometry ${catkin_LIBRARIES})

add_executable(odom_publisher src/nav/odom_publisher.cpp)
target_link_libraries(odom_publisher ${catkin_LIBRARIES})

add_executable(pointcloud_sub src/nav/pointcloud_sub.cpp)
target_link_libraries(pointcloud_sub ${catkin_LIBRARIES})
