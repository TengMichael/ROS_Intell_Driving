cmake_minimum_required(VERSION 2.8.3)
project(canbus)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp std_msgs message_generation
)


## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   candata.msg
   candata_multi.msg
#   Message2.msg
 )

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
 )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES canbus
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/canbus.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/canbus_node.cpp)
add_executable(can_device0 src/can_device0.cpp)
add_executable(can_device1 src/can_device1.cpp)
add_executable(can_device2 src/can_device2.cpp)
add_executable(cansend src/cansend.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(can_device0 can_device1 can_device2 cansend
    ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )
target_link_libraries(can_device0 ${catkin_LIBRARIES})
target_link_libraries(can_device1 ${catkin_LIBRARIES})
target_link_libraries(can_device2 ${catkin_LIBRARIES})

target_link_libraries(cansend ${catkin_LIBRARIES})

LINK_DIRECTORIES(${catkin_LIB_DIRS} lib)
target_link_libraries(can_device0 ${catkin_LIBRARIES} controlcan)
target_link_libraries(can_device1 ${catkin_LIBRARIES} controlcan)
target_link_libraries(can_device2 ${catkin_LIBRARIES} controlcan)

