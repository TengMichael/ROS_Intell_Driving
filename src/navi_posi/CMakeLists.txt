cmake_minimum_required(VERSION 2.8.3)
project(navi_posi)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp std_msgs message_generation serial
)
## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   vehicle_posture.msg
   navi_step.msg
   navi_route.msg
   navi_info.msg
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
add_executable(navi_position src/navi_position.cpp)
add_dependencies(navi_position
    ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(navi_position ${catkin_LIBRARIES})
#INCLUDE_DIRECTORIES(/usr/include/)
#LINK_DIRECTORIES(/usr/local/lib)
#target_link_libraries(${PROJECT_NAME} curl)
target_link_libraries(navi_position ${catkin_LIBRARIES} curl)
