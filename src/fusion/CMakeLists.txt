cmake_minimum_required(VERSION 2.8.3)
project(fusion)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp std_msgs message_generation
)
find_package(OpenCV REQUIRED)

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   fusion_obj.msg
   fusion_obj_multi.msg
   fusion_milradar_obj.msg
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
add_executable(fusion_data src/fusion_data.cpp)

add_dependencies(fusion_data
    ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(fusion_data ${catkin_LIBRARIES})
#target_link_libraries(fusion_display ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

target_link_libraries(fusion_data ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
