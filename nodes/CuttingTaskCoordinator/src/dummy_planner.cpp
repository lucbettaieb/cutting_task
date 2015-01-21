#include <ros/ros.h>

#include <CuttingTaskCoordinator/DummyPlannerAction.h>

int main(int argc, char** argv){
	ros::init(argc, argv, "dummy_planner");

	DummyPlannerActionServer as;
	
	ros::Rate rate(100);
	while(ros::ok()){
		ros::spinOnce();
		rate.sleep();
	}
}
