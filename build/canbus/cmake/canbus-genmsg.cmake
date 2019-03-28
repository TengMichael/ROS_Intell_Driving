# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "canbus: 2 messages, 0 services")

set(MSG_I_FLAGS "-Icanbus:/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(canbus_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg" NAME_WE)
add_custom_target(_canbus_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "canbus" "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg" ""
)

get_filename_component(_filename "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata_multi.msg" NAME_WE)
add_custom_target(_canbus_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "canbus" "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata_multi.msg" "canbus/candata"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(canbus
  "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/canbus
)
_generate_msg_cpp(canbus
  "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata_multi.msg"
  "${MSG_I_FLAGS}"
  "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/canbus
)

### Generating Services

### Generating Module File
_generate_module_cpp(canbus
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/canbus
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(canbus_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(canbus_generate_messages canbus_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg" NAME_WE)
add_dependencies(canbus_generate_messages_cpp _canbus_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata_multi.msg" NAME_WE)
add_dependencies(canbus_generate_messages_cpp _canbus_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(canbus_gencpp)
add_dependencies(canbus_gencpp canbus_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS canbus_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(canbus
  "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/canbus
)
_generate_msg_lisp(canbus
  "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata_multi.msg"
  "${MSG_I_FLAGS}"
  "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/canbus
)

### Generating Services

### Generating Module File
_generate_module_lisp(canbus
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/canbus
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(canbus_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(canbus_generate_messages canbus_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg" NAME_WE)
add_dependencies(canbus_generate_messages_lisp _canbus_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata_multi.msg" NAME_WE)
add_dependencies(canbus_generate_messages_lisp _canbus_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(canbus_genlisp)
add_dependencies(canbus_genlisp canbus_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS canbus_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(canbus
  "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/canbus
)
_generate_msg_py(canbus
  "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata_multi.msg"
  "${MSG_I_FLAGS}"
  "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/canbus
)

### Generating Services

### Generating Module File
_generate_module_py(canbus
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/canbus
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(canbus_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(canbus_generate_messages canbus_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata.msg" NAME_WE)
add_dependencies(canbus_generate_messages_py _canbus_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/canbus/msg/candata_multi.msg" NAME_WE)
add_dependencies(canbus_generate_messages_py _canbus_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(canbus_genpy)
add_dependencies(canbus_genpy canbus_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS canbus_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/canbus)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/canbus
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(canbus_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/canbus)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/canbus
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(canbus_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/canbus)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/canbus\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/canbus
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(canbus_generate_messages_py std_msgs_generate_messages_py)
endif()
