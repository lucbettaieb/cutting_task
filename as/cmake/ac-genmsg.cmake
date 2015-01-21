# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "ac: 7 messages, 0 services")

set(MSG_I_FLAGS "-Iac:/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg;-Iroscpp:/opt/ros/hydro/share/roscpp/cmake/../msg;-Istd_msgs:/opt/ros/hydro/share/std_msgs/cmake/../msg;-Iactionlib:/opt/ros/hydro/share/actionlib/cmake/../msg;-Iactionlib_msgs:/opt/ros/hydro/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(ac_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac
)
_generate_msg_cpp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac
)
_generate_msg_cpp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac
)
_generate_msg_cpp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac
)
_generate_msg_cpp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppFeedback.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac
)
_generate_msg_cpp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppAction.msg"
  "${MSG_I_FLAGS}"
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppFeedback.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppGoal.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionFeedback.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac
)
_generate_msg_cpp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppGoal.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac
)

### Generating Services

### Generating Module File
_generate_module_cpp(ac
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(ac_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(ac_generate_messages ac_generate_messages_cpp)

# target for backward compatibility
add_custom_target(ac_gencpp)
add_dependencies(ac_gencpp ac_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ac_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac
)
_generate_msg_lisp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac
)
_generate_msg_lisp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac
)
_generate_msg_lisp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac
)
_generate_msg_lisp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppFeedback.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac
)
_generate_msg_lisp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppAction.msg"
  "${MSG_I_FLAGS}"
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppFeedback.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppGoal.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionFeedback.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac
)
_generate_msg_lisp(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppGoal.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac
)

### Generating Services

### Generating Module File
_generate_module_lisp(ac
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(ac_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(ac_generate_messages ac_generate_messages_lisp)

# target for backward compatibility
add_custom_target(ac_genlisp)
add_dependencies(ac_genlisp ac_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ac_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac
)
_generate_msg_py(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac
)
_generate_msg_py(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac
)
_generate_msg_py(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac
)
_generate_msg_py(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppFeedback.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac
)
_generate_msg_py(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppAction.msg"
  "${MSG_I_FLAGS}"
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppFeedback.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppGoal.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionFeedback.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac
)
_generate_msg_py(ac
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/ac/msg/ppGoal.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac
)

### Generating Services

### Generating Module File
_generate_module_py(ac
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(ac_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(ac_generate_messages ac_generate_messages_py)

# target for backward compatibility
add_custom_target(ac_genpy)
add_dependencies(ac_genpy ac_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ac_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ac
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(ac_generate_messages_cpp roscpp_generate_messages_cpp)
add_dependencies(ac_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(ac_generate_messages_cpp actionlib_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ac
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(ac_generate_messages_lisp roscpp_generate_messages_lisp)
add_dependencies(ac_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(ac_generate_messages_lisp actionlib_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ac
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(ac_generate_messages_py roscpp_generate_messages_py)
add_dependencies(ac_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(ac_generate_messages_py actionlib_generate_messages_py)
