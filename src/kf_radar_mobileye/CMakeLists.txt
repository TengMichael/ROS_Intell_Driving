cmake_minimum_required(VERSION 2.8.3)
project(kf_radar_mobileye)

find_package(catkin REQUIRED COMPONENTS
  roscpp std_msgs message_generation
)
## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   radar_mobileye_data.msg
 )
## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
 )
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES serial
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)
include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)
add_executable(kalman_filter src/kalman_filter.cpp)
add_dependencies(kalman_filter
    ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(kalman_filter ${catkin_LIBRARIES})
