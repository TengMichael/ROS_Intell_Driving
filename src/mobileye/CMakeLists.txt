cmake_minimum_required(VERSION 2.8.3)
project(mobileye)

find_package(catkin REQUIRED COMPONENTS
  roscpp std_msgs message_generation
)
find_package(OpenCV REQUIRED)
## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   mobileye_Lane.msg
   mobileye_TSR.msg
   mobileye_TSR_multi.msg
   mobileye_Obstacle.msg
   mobileye_Obstacle_multi.msg
   mobileye_LKA_Lane.msg
   mobileye_LKA_Lane_multi.msg
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
add_executable(mobileye_com src/mobileye_com.cpp)

add_executable(mobileye_display src/mobileye_display.cpp)
add_dependencies(mobileye_com mobileye_display
    ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(mobileye_com ${catkin_LIBRARIES})
target_link_libraries(mobileye_display ${catkin_LIBRARIES})

target_link_libraries(mobileye_display ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
