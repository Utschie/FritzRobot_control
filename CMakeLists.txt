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

add_executable(joy_ext src/joy_ext.cpp)
target_link_libraries(joy_ext ${catkin_LIBRARIES})

add_executable(odometry_publisher src/nav/odometry_publisher.cpp)

if(nav_msgs_EXPORTED_TARGETS)
  add_dependencies(odometry_publisher ${nav_msgs_EXPORTED_TARGETS})
endif()

target_link_libraries(odometry_publisher ${catkin_LIBRARIES})


add_executable(gazebo_odometry src/nav/gazebo_odometry.cpp)
target_link_libraries(gazebo_odometry ${catkin_LIBRARIES})
