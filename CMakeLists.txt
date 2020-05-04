cmake_minimum_required(VERSION 2.8.3)
project(rostools)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

find_package(PCL REQUIRED)
find_package(OpenCV REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES rostools
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(rosbag_to_pcd src/rosbag_to_pcd.cpp)
target_link_libraries(rosbag_to_pcd ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(rosbag_to_image src/rosbag_to_image.cpp)
target_link_libraries(rosbag_to_image ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(rosbag_to_txt src/rosbag_to_txt.cpp)
target_link_libraries(rosbag_to_txt ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(display_pointcloudmaps_using_rviz src/display_pointcloudmaps_using_rviz.cpp)
target_link_libraries(display_pointcloudmaps_using_rviz ${catkin_LIBRARIES} ${PCL_LIBRARIES})

