//example_wall_cutting: test main
// this function illustrates how to use the class "TaskToJointInterp"
// in task space, define a desired cutting task as:

//example_wall_cutting: test main
// this function illustrates how to use the class "TaskToJointInterp"
// in task space, define a desired cutting task as:


#include <ros/ros.h>
#include <task_to_joint_interp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <joint_space_planner_awm14/JointSpacePlannerAction.h>
#include <Eigen/Eigen>
#include <actionlib/server/simple_action_server.h>
#include <math.h>
#include <string.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>


using namespace joint_space_planner_awm14;
Eigen::VectorXd penalty_weights;
Eigen::VectorXd starting_pose_8dof;
Eigen::VectorXd ending_pose_8dof;
Eigen::VectorXd g_x_rfoot, g_J_rfoot;


// This should go in a header

class JointSpacePlannerActionServer {
private:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<joint_space_planner_awm14::JointSpacePlannerAction> as_;

    joint_space_planner_awm14::JointSpacePlannerGoal goal_;
    joint_space_planner_awm14::JointSpacePlannerResult result_;
    joint_space_planner_awm14::JointSpacePlannerFeedback feedback_;

    TaskToJointInterp taskToJointInterp;

    std::vector<Eigen::VectorXd> compute_optimal_path(double, double, geometry_msgs::Polygon, int, double);
public:
    // Constructor
    JointSpacePlannerActionServer();

    // Action server primary invokable action
    void computePath(
            const actionlib::SimpleActionServer<joint_space_planner_awm14::JointSpacePlannerAction>::GoalConstPtr& goal);

};


#define NUMBER_OF_SUBSEGMENTS 10
#define APPROACH_DISTANCE 0.0 //.08


// Crazy constructor...

JointSpacePlannerActionServer::JointSpacePlannerActionServer() :
as_(nh_, "joint_space_planner", boost::bind(&JointSpacePlannerActionServer::computePath, this, _1), false) {
    ROS_INFO("in constructor of JointSpacePlannerActionServer");
    // do any other desired initializations here...specific to your implementation

    as_.start(); //start the server running

}

Eigen::Vector2d get_nth_vertex_in_wall_frame(int n, std::vector<geometry_msgs::Point32> poly_line, double wall_angle, double wall_distance) {
    //	std::cout<<"get_nth_vertex_in_wall_frame called \n";

    geometry_msgs::Point32 nth_vertex_point = poly_line[n];
    Eigen::Vector3d nth_vertex(nth_vertex_point.x, nth_vertex_point.y, nth_vertex_point.z); // Inefficient, infrequent operation. Not important enough to fix.

    // The wall normal is pointing at the robot
    double wall_normal_x = -sin(wall_angle); // x is along the axis which is parallel to walking foward.
    double wall_normal_y = -cos(wall_angle); // y is along the axis which is parallel to walking to the left.
    double wall_normal_z = 0.0;


    Eigen::Vector3d wall_normal(wall_normal_x, wall_normal_y, wall_normal_z);
    Eigen::Vector3d wall_origin = wall_normal * -wall_distance;
    double vertex_distance_to_wall = wall_normal.dot(nth_vertex - wall_origin);
    Eigen::Vector3d closest_point_on_wall_from_vertex = nth_vertex - vertex_distance_to_wall * wall_normal;
    Eigen::Vector3d closest_point_relative_to_origin = closest_point_on_wall_from_vertex - wall_origin;
    Eigen::Vector3d z_axis(0.d, 0.d, 1.d);
    Eigen::Vector3d y_axis_in_wall = -wall_normal.cross(z_axis);
    double y_displacement = y_axis_in_wall.dot(closest_point_relative_to_origin);
//    
//    tf::TransformListener tf_listener; // create a transform listener object
//    tf::StampedTransform transform; // holder for transform result
//    tf::Vector3 frame_origin; // 3x1 vector to hold origin of right grasp frame
//
//    //wait until receive valid frames
//    bool tf_not_ready = true;
//    int ntries = 0;
//    while (tf_not_ready) {
//        try {
//            tf_not_ready = false;
//            tf_listener.lookupTransform("/pelvis", "/r_foot", ros::Time(0), transform);
//        } catch (tf::TransformException ex) { //do nothing
//            tf_not_ready = true;
//            ntries++;
//            ROS_INFO("waiting for pelvis frame; ntries = %d", ntries);
//            ros::Duration(0.3).sleep();
//        }
//    }
//    
//    tf_listener.lookupTransform("/pelvis", "/r_foot", ros::Time(0), transform); //offset of pelvis height
//    frame_origin = transform.getOrigin();
//    
//    double z_displacement = nth_vertex[2] - frame_origin[2] + 0.05;
    double z_displacement = nth_vertex[2];
    //ROS_INFO("Z displacement %d", z_displacement);
    
    std::cout << "displacement in the plane of the wall: <y, z> = " << y_displacement << ", " << z_displacement << std::endl;
    return Eigen::Vector2d(y_displacement, z_displacement);
}

eigen_to_msg::vec8dof convert_vectorxd_to_vec8dof(Eigen::VectorXd original) {
    //	std::cout<< "convert_vectorxd_to_vec8dof called\n";
    eigen_to_msg::vec8dof result;
    result.a0 = original[0];
    result.a1 = original[1];
    result.a2 = original[2];
    result.a3 = original[3];
    result.a4 = original[4];
    result.a5 = original[5];
    result.a6 = original[6];
    result.a7 = original[7];

    return result;

}

std::vector<eigen_to_msg::vec8dof> convert_vector_vectorxd_to_vec8dof(std::vector<Eigen::VectorXd> original) {
    //	std::cout<<"convert_vector_vectorxd_to_vec8dof called\n";

    std::vector<eigen_to_msg::vec8dof> result;
    for (int a = 0; a < original.size(); a++) {
        Eigen::VectorXd incoming_data = original[a];

        if (incoming_data.innerSize() != 8) {
            ROS_INFO("convert_vectorxd_to_vec8dof received a vectorxd with a size other than 8");
            throw -1; //Ew :( Can't I use asserts or something?
        }
        result.push_back(convert_vectorxd_to_vec8dof(incoming_data)); // Should this be a reference variable??? Is this making a completely pointless copy of this object?
    }
    return result;
}

//		eigen_to_msg::vec_of_vec8dof compute_optimal_path(double, double, geometry_msgs::Polygon, int, double);

std::vector<Eigen::VectorXd> JointSpacePlannerActionServer::compute_optimal_path(double wall_distance, double wall_angle, geometry_msgs::Polygon poly_line, int number_of_subsegments, double approach_distance) {

    //	std::cout<<"compute_optimal_path called\n";
    // This variable gets used multiple places in order to store whether or not a line segment was reachable.
    bool is_good_lineseg = false;

    // define a coordinate frame on the wall, with respect to local world frame;
    // the wall orientation is defined to have z-axis pointing up (w/rt pelvis frame, i.e. parallel to z_pelvis)
    // and with x-axis pointing into the wall (antiparallel to the surface normal)
    // at wall_ang=0, Atlas is facing the wall, with his pelvis x-axis parallel to the wall-frame x-axis
    // at this pose, the wall-frame orientation is aligned with Atlas's pelvis frame orientation
    // wall_ang specifies rotating the wall about vertical;  a small, positive value of wall_ang results in the
    // wall x-axis pointing mostly along the pelvis x-axis, and slightly along the positive pelvis y-axis
    // More generally, the wall-frame axes, expressed in the pelvis frame, are:
    Eigen::Matrix3d Rwall;
    Rwall << cos(wall_angle), -sin(wall_angle), 0,
            sin(wall_angle), cos(wall_angle), 0,
            0, 0, 1;

    Eigen::Vector3d z_hand;
    z_hand << 0, 0, 1; // start w/ z-hand pointing up
    Eigen::Vector3d y_hand = Rwall.col(0); //since the wall-frame x-axis points INTO the wall, choose this for the desired hand orientation
    Eigen::Vector3d x_hand = y_hand.cross(z_hand); // just make sure x_hand is consistent with z and y

    Eigen::Matrix3d desired_hand_orientation;
    desired_hand_orientation.col(0) = x_hand;
    desired_hand_orientation.col(1) = y_hand;
    desired_hand_orientation.col(2) = z_hand;

    // We could compute the closest point on the wall, then take a normal projection away from that point... but instead, just use the first point we have in the Polygon
    Eigen::Vector3d desired_hand_position;
    std::vector<geometry_msgs::Point32> point_vector = poly_line.points;

    int point_vector_size = point_vector.size();
    std::cout << "point vector size: " << point_vector_size << std::endl;

    geometry_msgs::Point32 first_point = point_vector.front();

    //	std::cout << first_point << std::endl;

    desired_hand_position(0) = first_point.x;
    desired_hand_position(1) = first_point.y;
    desired_hand_position(2) = first_point.z;


    // This is where we will store the best joint-space-path to take, in order to follow the polyline
    std::vector<Eigen::VectorXd> optimal_path;


    // Compute the approach orientation
    Eigen::Matrix3d approach_orientation;
    approach_orientation = desired_hand_orientation;
    //	std::cout<<"compute_optimal_path called\n";

    // Compute the approach position
    Eigen::Vector3d approach_position;
    approach_position = desired_hand_position - Rwall.col(0) * approach_distance;
    //	std::cout<<"compute_optimal_path called\n";

    // Combine them into an Eigen::Affine3d object
    Eigen::Affine3d approach_orientation_and_position;
    approach_orientation_and_position.linear() = approach_orientation;
    approach_orientation_and_position.translation() = approach_position;

    //	ROS_INFO("about to call compute_task_line_seg_to_jnt_space");
    is_good_lineseg = taskToJointInterp.compute_task_line_seg_to_jnt_space(approach_orientation_and_position, 0, 0, 1);
    if (!is_good_lineseg) {
        ROS_WARN("Received unreachable start segment, halting");
        throw -1;
    }

    std::vector<Eigen::VectorXd> path_segment_buffer;
    taskToJointInterp.compute_optimal_path();
    taskToJointInterp.get_soln(path_segment_buffer);

    // Grab the first pose and call it the approach pose. This will be used as the starting_pose for the first line segment
    optimal_path.push_back(path_segment_buffer.front());

    for (int n = 1; n < poly_line.points.size() - 1; n++) {

        Eigen::Vector2d yz_segment_start = get_nth_vertex_in_wall_frame(n - 1, poly_line.points, wall_angle, wall_distance);
        Eigen::Vector2d yz_segment_end = get_nth_vertex_in_wall_frame(n, poly_line.points, wall_angle, wall_distance);

        double delta_y = yz_segment_end[0] - yz_segment_start[0];
        double delta_z = yz_segment_end[1] - yz_segment_start[1];

        // Determine how the hand should be oriented
        Eigen::Affine3d hand_position_at_start_of_segment;
        hand_position_at_start_of_segment.linear() = desired_hand_orientation;

        // Determine how the hand should be positioned in Cartesian coords
        Eigen::Vector3d hand_translation_at_start_of_segment;
        geometry_msgs::Point32 current_start_point = poly_line.points[n - 1];
        hand_translation_at_start_of_segment(0) = current_start_point.x;
        hand_translation_at_start_of_segment(1) = current_start_point.y;
        hand_translation_at_start_of_segment(2) = current_start_point.z;
        hand_position_at_start_of_segment.translation() = hand_translation_at_start_of_segment;

        // here, call WSN's function, which in turn computes all viable poses which we can use to trace the specified line segment
        taskToJointInterp.set_start_pose(optimal_path.back());
        is_good_lineseg = taskToJointInterp.compute_task_line_seg_to_jnt_space_without_clearing_history(hand_position_at_start_of_segment, delta_y, delta_z, number_of_subsegments);

        if (!is_good_lineseg) {
            ROS_WARN("Received untraceable line segment, halting");
            throw -1;
        }
    }
    taskToJointInterp.compute_optimal_path();
    taskToJointInterp.get_soln(optimal_path);
    taskToJointInterp.clearPath();
    return optimal_path;
}

void JointSpacePlannerActionServer::computePath(const actionlib::SimpleActionServer<joint_space_planner_awm14::JointSpacePlannerAction>::GoalConstPtr& goal) {

    try {
        result_.error_code = 0;
        eigen_to_msg::vec_of_vec8dof empty;
        result_.suggested_joint_path = empty; //new vector<eigen_to_msg::vec8dof>();
        double wall_distance = goal->wall_distance;
        double wall_angle = goal->wall_angle;
        geometry_msgs::Polygon poly_line = goal->desired_R3_path;
        std::vector<Eigen::VectorXd> optimal_path;
        std::vector<Eigen::VectorXd> smoothed_path;
        std::cout << "input length:" << goal->desired_R3_path.points.size();

        if (goal->desired_R3_path.points.size() > 0) {

            std::cout << poly_line;
            // Actually compute the path we should take

            std::vector<Eigen::VectorXd> result_path = compute_optimal_path(wall_distance, wall_angle, poly_line, NUMBER_OF_SUBSEGMENTS, APPROACH_DISTANCE);

            // Shove it in a result and notify all waiting clients that we have succeeded.
            eigen_to_msg::vec_of_vec8dof converted_path;
            converted_path.vecs8dof = convert_vector_vectorxd_to_vec8dof(result_path);
            result_.suggested_joint_path = converted_path;
        }
        std::cout << "JOINT SPACE PLANNER THINKS IT IS DONE\n";
        std::cout << "JOINT SPACE PLANNER THINKS IT IS DONE\n";
        std::cout << "JOINT SPACE PLANNER THINKS IT IS DONE\n";
        std::cout << "JOINT SPACE PLANNER THINKS IT IS DONE\n";
        std::cout << "JOINT SPACE PLANNER THINKS IT IS DONE\n";
        std::cout << "JOINT SPACE PLANNER THINKS IT IS DONE\n";
        std::cout << "JOINT SPACE PLANNER THINKS IT IS DONE\n";

        as_.setSucceeded(result_);
    } catch (int ex) {
        std::cout << "caught exception while trying to compute the joint-space-path\n";
        result_.error_code = ex;
        result_.error_name = "Likely found an unreachable point in the trajectory";
        as_.setAborted(result_);
    }
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "joint_space_planner_awm14");

    JointSpacePlannerActionServer as;
    cout << "test\n";
    ros::Rate rate(100);
    ros::spinOnce();
    tf::TransformListener tf_listener; // create a transform listener object
    tf::StampedTransform transform; // holder for transform result
    tf::Vector3 frame_origin; // 3x1 vector to hold origin of right grasp frame

    //wait until receive valid frames
    bool tf_not_ready = true;
    int ntries = 0;
    while (tf_not_ready) {
        try {
            tf_not_ready = false;
            tf_listener.lookupTransform("/pelvis", "/r_foot", ros::Time(0), transform);
        } catch (tf::TransformException ex) { //do nothing
            tf_not_ready = true;
            ntries++;
            ROS_INFO("waiting for pelvis frame; ntries = %d", ntries);
            ros::Duration(0.3).sleep();
        }
    }
    
    tf_listener.lookupTransform("/pelvis", "/r_foot", ros::Time(0), transform);
    frame_origin = transform.getOrigin();
    ROS_INFO("pelvis height with respect to the r_foot : %f and respect to the ground: %f", -frame_origin[2],-frame_origin[2]+0.05);

    while (ros::ok()) {
        ros::spinOnce();
        rate.sleep();
        // I don't really understand why this is necessary, wouldn't the JointSpacePlannerActionServer start its own thread via the boost/bind stuff?
        // Unless spinOnce is literally telling as that it should check for input.........
    }
}
