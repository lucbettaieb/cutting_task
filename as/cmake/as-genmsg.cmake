# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "as: 7 messages, 0 services")

set(MSG_I_FLAGS "-Ias:/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg;-Iroscpp:/opt/ros/hydro/share/roscpp/cmake/../msg;-Iatlas_msgs:/opt/ros/hydro/share/atlas_msgs/cmake/../msg;-Itrajectory_msgs:/opt/ros/hydro/share/trajectory_msgs/cmake/../msg;-Iactionlib:/opt/ros/hydro/share/actionlib/cmake/../msg;-Iactionlib_msgs:/opt/ros/hydro/share/actionlib_msgs/cmake/../msg;-Ihku_msgs:/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/hku_msgs/msg;-Ihku_msgs:/home/bxc237/ros_workspace/team_hku_drc/catkin/src/hku_msgs/msg;-Itf:/opt/ros/hydro/share/tf/cmake/../msg;-Igeometry_msgs:/opt/ros/hydro/share/geometry_msgs/cmake/../msg;-Itask_variables:/home/bxc237/ros_workspace/team_hku_drc/catkin/src/kinematics_stack/task_variables/msg;-Ijacobian_publisher:/home/bxc237/ros_workspace/team_hku_drc/catkin/src/kinematics_stack/jacobian_publisher/msg;-Imanipulation_balancing:/home/bxc237/ros_workspace/team_hku_drc/catkin/src/manipulation_balancing/msg;-Imanipulation_balancing:/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/manipulation_balancing/msg;-Istd_msgs:/opt/ros/hydro/share/std_msgs/cmake/../msg;-Ieigen_to_msg:/home/bxc237/ros_workspace/team_hku_drc/catkin/src/examples/eigen_to_msg/msg;-Isensor_msgs:/opt/ros/hydro/share/sensor_msgs/cmake/../msg;-Iosrf_msgs:/opt/ros/hydro/share/osrf_msgs/cmake/../msg;-Isandia_hand_msgs:/opt/ros/hydro/share/sandia_hand_msgs/cmake/../msg;-Icontrol_msgs:/opt/ros/hydro/share/control_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(as_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as
)
_generate_msg_cpp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppFeedback.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as
)
_generate_msg_cpp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppAction.msg"
  "${MSG_I_FLAGS}"
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppFeedback.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionFeedback.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionGoal.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionResult.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppGoal.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as
)
_generate_msg_cpp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppGoal.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as
)
_generate_msg_cpp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as
)
_generate_msg_cpp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as
)
_generate_msg_cpp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as
)

### Generating Services

### Generating Module File
_generate_module_cpp(as
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(as_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(as_generate_messages as_generate_messages_cpp)

# target for backward compatibility
add_custom_target(as_gencpp)
add_dependencies(as_gencpp as_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS as_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as
)
_generate_msg_lisp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppFeedback.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as
)
_generate_msg_lisp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppAction.msg"
  "${MSG_I_FLAGS}"
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppFeedback.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionFeedback.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionGoal.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionResult.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppGoal.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as
)
_generate_msg_lisp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppGoal.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as
)
_generate_msg_lisp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as
)
_generate_msg_lisp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as
)
_generate_msg_lisp(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as
)

### Generating Services

### Generating Module File
_generate_module_lisp(as
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(as_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(as_generate_messages as_generate_messages_lisp)

# target for backward compatibility
add_custom_target(as_genlisp)
add_dependencies(as_genlisp as_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS as_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as
)
_generate_msg_py(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppFeedback.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as
)
_generate_msg_py(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppAction.msg"
  "${MSG_I_FLAGS}"
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppFeedback.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionFeedback.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionGoal.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionResult.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppGoal.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as
)
_generate_msg_py(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppGoal.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as
)
_generate_msg_py(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppResult.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/hydro/share/actionlib_msgs/cmake/../msg/GoalID.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as
)
_generate_msg_py(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as
)
_generate_msg_py(as
  "/home/bxc237/ros_workspace/team_hku_drc/catkin/devel/share/as/msg/ppResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as
)

### Generating Services

### Generating Module File
_generate_module_py(as
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(as_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(as_generate_messages as_generate_messages_py)

# target for backward compatibility
add_custom_target(as_genpy)
add_dependencies(as_genpy as_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS as_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/as
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(as_generate_messages_cpp roscpp_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp atlas_msgs_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp trajectory_msgs_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp actionlib_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp hku_msgs_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp tf_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp task_variables_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp jacobian_publisher_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp manipulation_balancing_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp low_level_joint_controller_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(as_generate_messages_cpp eigen_to_msg_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/as
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(as_generate_messages_lisp roscpp_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp atlas_msgs_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp trajectory_msgs_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp actionlib_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp hku_msgs_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp tf_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp task_variables_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp jacobian_publisher_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp manipulation_balancing_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp low_level_joint_controller_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(as_generate_messages_lisp eigen_to_msg_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/as
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(as_generate_messages_py roscpp_generate_messages_py)
add_dependencies(as_generate_messages_py atlas_msgs_generate_messages_py)
add_dependencies(as_generate_messages_py trajectory_msgs_generate_messages_py)
add_dependencies(as_generate_messages_py actionlib_generate_messages_py)
add_dependencies(as_generate_messages_py actionlib_msgs_generate_messages_py)
add_dependencies(as_generate_messages_py hku_msgs_generate_messages_py)
add_dependencies(as_generate_messages_py tf_generate_messages_py)
add_dependencies(as_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(as_generate_messages_py task_variables_generate_messages_py)
add_dependencies(as_generate_messages_py jacobian_publisher_generate_messages_py)
add_dependencies(as_generate_messages_py manipulation_balancing_generate_messages_py)
add_dependencies(as_generate_messages_py low_level_joint_controller_generate_messages_py)
add_dependencies(as_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(as_generate_messages_py eigen_to_msg_generate_messages_py)
