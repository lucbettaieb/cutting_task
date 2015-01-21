#include <ros/ros.h>

#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <joint_space_planner_awm14/JointSpacePlannerAction.h>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>


void doneCb(const actionlib::SimpleClientGoalState& state,
        const joint_space_planner_awm14::JointSpacePlannerResultConstPtr& result) {
	ROS_INFO("Joint space planner is finished: error_code");
	std::cout << (result->error_code) << std::endl;
	std::cout << "number of joint positions in the final path: "  << result -> suggested_joint_path.vecs8dof.size() << std::endl;
	
	if(result->error_code != 0) {
		ROS_INFO("Joint space planner couldn't find a path");
		return;
	}
	ROS_INFO("Joint space planner found a path");
	
	std::vector<eigen_to_msg::vec8dof> joint_path = result -> suggested_joint_path.vecs8dof;

	for(int a=0; a < joint_path.size(); a++)
	{
		std::cout << "joint_path.a0" << joint_path[a].a0 << "\t";
		std::cout << "joint_path.a1" << joint_path[a].a1 << "\t";
		std::cout << "joint_path.a2" << joint_path[a].a2 << "\t";
		std::cout << "joint_path.a3" << joint_path[a].a3 << "\t";
		std::cout << "joint_path.a4" << joint_path[a].a4 << "\t";
		std::cout << "joint_path.a5" << joint_path[a].a5 << "\t";
		std::cout << "joint_path.a6" << joint_path[a].a6 << "\t";
		std::cout << "joint_path.a7" << joint_path[a].a7 << "\t";
		std::cout << std::endl;
	}
	exit(0);
}

void activeCb() {
    ROS_INFO("Goal just went active");

}

void feedbackCb(const joint_space_planner_awm14::JointSpacePlannerFeedbackConstPtr& feedback) {
}

void generateTestR3Path(int numberOfVertices, std::vector<geometry_msgs::Point32>& buffer, float horizontal_offset, float vertical_offset, float depth_offset, float radius) {
	std::cout << "starting generation of vertices\n";
	for(int a=0; a<numberOfVertices; a++) {
		geometry_msgs::Point32 vertex;
		// Since these points are for the arm, lets put them .5 meters in front of us, and basically in a circle.
		vertex.x = depth_offset;

		float angle = 2.0 * M_PI * (a/(double)(numberOfVertices));

		//y corresponds to the normal x axis, if we're looking at the wall
		vertex.y = cos(angle) * radius + horizontal_offset;

		//z corresponds to the normal y axis, if we're looking at the wall
		vertex.z = sin(angle) * radius + vertical_offset;
		buffer.push_back(vertex);
	}
}

int main(int argc, char **argv) {
	std::cout << "launched test_joint_space_client" << std::endl;
	ros::init(argc, argv, "test_joint_space_client");
	ros::start();
	ros::Rate rate(100);
	// Create the action client
	actionlib::SimpleActionClient<joint_space_planner_awm14::JointSpacePlannerAction> ac("joint_space_planner", true);

	std::cout << "enter the radius of the circle in meters: "; 
	float radius = 0;
	std::cin >> radius;
	for(float horizontal_offset = -0.2; horizontal_offset < 0; horizontal_offset +=0.01) {
		for(float vertical_offset = .5; vertical_offset < 0.7; vertical_offset += 0.01) {
			for(float depth_offset = 0.5; depth_offset < 0.7; depth_offset += 0.01) {
	//			for(float radius = 0; radius < 0.2; radius += 0.01) {
					if(!ros::ok()) {
						return -1;
					}
					joint_space_planner_awm14::JointSpacePlannerGoal goal;
					generateTestR3Path(4, goal.desired_R3_path.points, horizontal_offset, vertical_offset, depth_offset, radius);
					std::cout << "4\n";
					ROS_INFO("checking for live actionServer...");
					ac.waitForServer();
					ROS_INFO("Action server is running, sending goal.");
					ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
					ac.waitForResult(ros::Duration(10));
	//			}
			}
		}
	}
	while(ros::ok()) {
		ros::spinOnce();
		rate.sleep();
	}
	return 0;
}
