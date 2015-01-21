###Readme for Assignment 10
------------------------------
#####About
This an 'after the fact' repository for my final project for eecs397: software development for the darpa robotics challenge.  The purpose of this project was to make ATLAS perform an intergrated wall-cut.  First, a wall would be identified via a point cloud.  Next, a poly-line would be created on that wall.  After running certain computations, atlas would then 'cut'* the points of the polyline.  It never worked 100%, but it did perform the behavior requested!

*not cut, trace.
#####Project video:
https://www.youtube.com/watch?v=xvdxuhTOwYc

#####Setup instuctions (must run from drc_class repo)
VRC_CHEATS_ENABLED=1 roslaunch hku_worlds drc_practice_task_6.launch

For better visibility, delete "starting pen" model.
Move Atlas backwards but do not rotate him.  Rotating causes issues.
Move and rotate the cutout_wall model in front of Atlas at a reasonable distance.

rostopic pub --once /atlas/mode std_msgs/String '{data: "pinned_with_gravity"}'

^Do this to avoid further issues!

rosrun rviz rviz
...In rviz, Add LaserScan and Marker to the "Displays" panel.
...also should have a pointStamped
rostopic pub --once /multisense_sl/set_spindle_speed std_msgs/Float64 '{data: 3.0}'

rosrun joint_space_planner_awm14 joint_space_planner_awm14 

////////////////////////////////////////
rosrun CuttingTaskCoordinator cut_controller
////////////////////////////////////////
AT FIRST BREAKPOINT perform the following steps:

rosrun wall_finder wall_finder_selected_points_node
rostopic echo /plane_info
...Look at output of echo
...Manually select points in RViz using publish selected points. These should correspond to the wall.
...save these values
...ctrl-c wall_finder_selected_points_node

rosrun lxs_wall_cuttability_ik cuttability_region

rosrun lxs_polyline_vertices_selector polyline_vertices_selector
rosrun lxs_polyline_marker polyline_marker_listener

...use publish selected points in rviz to select points for the polyline.
......pointStamped should be subscribed to /centroidStamped
......Marker should be subscribed to /polyline_marker_publisher


*...when you are ready to publish the polyline, send a 'click' by
rostopic pub -r 10 click std_msgs/Bool 1


Now after your click is being published, bumings server is running
1. roslaunch fc_bringup sim_task_4.launch 
2. rosrun sim_controller USER
3. rosrun example_filter foot_wrench_filter_node (for balance)
4. rosrun jacobian_publisher jacobian_publisher (for balance)
5. rosrun as ppas
6. rosrun as ppac


Now go back to the controller and enter 0 to exit the breakpoint.
!!If nothing happens, ppac likely crashed.  This is normal(?) Restart ppac and go through both breakpoints in the controller again
Atlas should start moving!
