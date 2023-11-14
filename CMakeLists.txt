cmake_minimum_required(VERSION 3.0.2)
project(fritzrobot_control)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs
)


include_directories(
  ${catkin_INCLUDE_DIRS}
  include/${PROJECT_NAME}/
)

add_executable(joy_ext src/joy_ext.cpp)
target_link_libraries(joy_ext ${catkin_LIBRARIES})

