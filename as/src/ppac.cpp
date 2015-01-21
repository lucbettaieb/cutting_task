#include<ros/ros.h>

#include <actionlib/client/simple_action_client.h>

#include<as/ppAction.h>
//this #include refers to the new "action" message defined for this package
// the action message can be found in: .../as/action/pp.action
// automated header generation creates multiple headers for message I/O
// these are referred to by the root name (action) and appended name (Action)
// If you write a new client of the server in this package, you will need to include as in your package.xml,
// and include the header file below
#include <iostream>

#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/LU>

#include <atlas_msgs/AtlasState.h>
#include <atlas_conversions/joint_names.h>
#include <std_msgs/Bool.h>
#include <hku_msgs/vectorOfDoublesWHeader.h>

#include <hku_msgs/TrackJointTrajectoryAction.h>  // this includes the ActionGoal, ActionResult, and ActionFeedback.h headers

#include <vector>
#include "eigen_to_msg.h"

using namespace std;
using namespace Eigen;

bool succeeded = true;
double g_jointAngles[NJoints];
Eigen::Matrix<double, 7, 1> q_vec_7d;
std::vector<Vectorq8x1> g_path;
bool message_receive = false;

void getJointStatesCB(const atlas_msgs::AtlasState& js) {
	for (unsigned int i = 0; i < NJoints; i++) {
		g_jointAngles[i] = js.position[i]; //copy to global var
	}
}

void messageCB(const eigen_to_msg::vec_of_vec8dof& vec_of_vec8dof_msg) {
	if (succeeded == false)
		ROS_INFO("not ready for the new message");
	else {
		ROS_INFO("receive new message!");
		succeeded = false;
		RosMsgToVecOf8DofEvecs(vec_of_vec8dof_msg, g_path); // convert message to 8x1 Eigen::Vector type, which is global
		cout << "path received: " << endl; // debug output
		for (int i = 0; i < g_path.size(); i++) {
			cout << g_path[i].transpose() << endl;
		}
		message_receive = true;
	}
}

//this is the function will convert all comments for 6 right arm joints and 1 utorso joint to joint trajectory behavior action message   
void stuff_goal_message_w_qvec(Eigen::Matrix<double, 7, 1> q_vec,
		hku_msgs::TrackJointTrajectoryGoal &goal) {

	int NJointsActive = 7; // this example is restricted to controller the 6 joints of the right arm

	hku_msgs::JointTrajectoryExtended des_hand_trajectory;

	// list the involved joint names and specify the corresponding joint control modes (hard coded as mode 1)
	des_hand_trajectory.trajectory.joint_names.resize(0); //erase former entries
	des_hand_trajectory.joint_mode.resize(0);
	for (int ijnt = 21; ijnt < 28; ijnt++) {
		if (ijnt == 21) {
			des_hand_trajectory.trajectory.joint_names.push_back(
					atlas::jointNameFromIdx(0));
			des_hand_trajectory.joint_mode.push_back(1);
		} else {
			des_hand_trajectory.trajectory.joint_names.push_back(
					atlas::jointNameFromIdx(ijnt));
			des_hand_trajectory.joint_mode.push_back(1);
		}
	}

	int NTrajPoints = 1; // for this example, there is only one destination point.
	double timeIntervalBtwEachPnt = 3.0; // hard code move time to 3 sec

	des_hand_trajectory.trajectory.points.resize(NTrajPoints);

	// Intialize all points; in this simple example, "all" points is just a single point
	for (int ipt = 0; ipt < NTrajPoints; ipt++) {
		des_hand_trajectory.trajectory.points[ipt].positions.resize(
				NJointsActive);
		des_hand_trajectory.trajectory.points[ipt].velocities.resize(
				NJointsActive);
		for (int ijnt = 0; ijnt < NJointsActive; ijnt++) {
			des_hand_trajectory.trajectory.points[ipt].positions[ijnt] = q_vec(
					ijnt);
			des_hand_trajectory.trajectory.points[ipt].velocities[ijnt] = 0;
		}
	}

	// The trajectory goal message time stamp
	des_hand_trajectory.trajectory.header.stamp = ros::Time::now(); // + ros::Duration(1.0);

	for (int ipt = 0; ipt < NTrajPoints; ipt++) {
		//desired arrival time for each point
		des_hand_trajectory.trajectory.points[ipt].time_from_start =
				ros::Duration(((double) ipt + 1) * timeIntervalBtwEachPnt);
	}

	goal.trajectory.resize(0); //erase former goal trajectories
	goal.trajectory.push_back(des_hand_trajectory);
	ROS_INFO("done stuffing goal with data ");

}

// This function will be called once when the goal completes
// this is optional, but it is a convenient way to get access to the "result" message sent by the server

void doneCbpp(const actionlib::SimpleClientGoalState& state,
		const as::ppResultConstPtr& result) {
	ROS_INFO(" doneCb: server responded with state [%s]",
			state.toString().c_str());
	//int diff = result->output - result->goal_stamp;
	//ROS_INFO("got result output = %d; goal_stamp = %d; diff = %d",result->output,result->goal_stamp,diff);
	ROS_INFO("current height of pelvis: %f", result->height);
	//ROS_INFO("11111111111111111111111111111111"); //to display something to check if 2 action servers
	//finish their goals at the same time
}

void doneCbtraj(const actionlib::SimpleClientGoalState& state,
		const hku_msgs::TrackJointTrajectoryResultConstPtr& result) {
	ROS_INFO(" doneCb: server responded with state [%s]",
			state.toString().c_str());
	ROS_INFO(" Finish arm and utorso movement");
	//ROS_INFO("222222222222222222222222222222222");//to display something to check if 2 action servers
	//finish their goals at the same time
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "action_client"); // name this node

	//////////////////////////////////////////////////////////////////////
	ros::NodeHandle nh;
	ros::NodeHandle nhluc;
	ros::Rate timer(1);
	ROS_INFO("setting up subscriber to atlas state");
	ros::Subscriber sub = nh.subscribe("/atlas/atlas_state", 1,
			getJointStatesCB);
	g_jointAngles[0] = 1000.0;
	//let the subscriber get joint-state data to use for command initialization;
	ROS_INFO("waiting for valid sensor data: ");
	while (g_jointAngles[0] > 100.0) {
		ros::spinOnce(); // let the callback process incoming messages
		timer.sleep(); //sleep for 1 sec
		ros::spinOnce(); //give the callback another chance...
		ROS_INFO("jnt0 = %f", g_jointAngles[0]);
	}

	for (int ijnt = 21; ijnt < 28; ijnt++) {
		if (ijnt == 21)
			q_vec_7d(0) = g_jointAngles[0];
		else
			q_vec_7d(ijnt - 21) = g_jointAngles[ijnt];
	}

	ros::Subscriber sub_luc = nhluc.subscribe("/team1/ac", 1, messageCB);

	hku_msgs::TrackJointTrajectoryGoal trajgoal; //declare the goal for joint trajectory behavior client and server

	actionlib::SimpleActionClient < hku_msgs::TrackJointTrajectoryAction
			> trajac("/joint_traj_behavior", true); //declare the joint trajectory behavior client, trajac, and connect it to
			//joint trajectory behavior server, which was named "/joint_traj_behavior"

	unsigned int attempts = 0;
	while (ros::ok() && !trajac.waitForServer(ros::Duration(5.0))
			&& ++attempts < 3)
		ROS_INFO_STREAM("waiting for traj behavior action server");

	if (!trajac.isServerConnected()) {
		ROS_ERROR_STREAM("Action client not connected; giving up");
		return 0;
	}
	ROS_INFO("connected to joint-trajectory action server");

	as::ppGoal ppgoal; //declare the goal for pelvis position client and server ("as" is the name of this package and "pp" is
	//the name of the action message defined in "action" folder)

	// use the name of our server, which is: pp_action (named in as.cpp)
	actionlib::SimpleActionClient < as::ppAction
			> ppac("pelvis_position_action", true);

	// attempt to connect to the server:
	attempts = 0;
	while (ros::ok() && !ppac.waitForServer(ros::Duration(5.0))
			&& ++attempts < 3)
		ROS_INFO_STREAM("waiting for pelvis position action server");

	if (!ppac.isServerConnected()) {
		ROS_ERROR_STREAM("could not connect to server; halting");
		return 0;
	}

	ROS_INFO("connected to pelvis position action server"); // if here, then we connected to the server;
	while (message_receive == false) {
		ros::spinOnce(); // let the callback process incoming messages
		timer.sleep(); //sleep for 1 sec
		ros::spinOnce(); //give the callback another chance...
		ROS_INFO("waiting luc's message......");
	}

	while (1) {
		// stuff a goal message:
		if (succeeded == false) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 7; j++) {
					ppgoal.height = g_path[i][0];
					ppgoal.duration = 3; //define the moving duration for the pelvis position movement, here is 3 sec
					q_vec_7d(j) = g_path[i][j + 1];
				}
				//q_vec_7d = Eigen::Matrix<double, 7, 1>::Zero();
				//q_vec_7d(0) = 0.5; //this is joint comment for one of the utorso joint rotating about Z axis
				stuff_goal_message_w_qvec(q_vec_7d, trajgoal);
				ROS_INFO("target height: %f", ppgoal.height);
				//action clients for pelvis position and trajectory behavior send their goal separately
				ppac.sendGoal(ppgoal, &doneCbpp);// we could also name additional callback functions here, if desired
				trajac.sendGoal(trajgoal, &doneCbtraj);
				//    action_client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb); //e.g., like this

				//bool finished_before_timeout = action_client.waitForResult(ros::Duration(5.0));
				//bool finished_before_timeout = action_client.waitForResult(); // wait forever...
				ppac.waitForResult();
				trajac.waitForResult();
				//        if (!finished_before_timeout) {
				//            ROS_WARN("giving up waiting on result for goal ");
				//            return 0;
				//        }
				//        else {
				//          //if here, then server returned a result to us
				//        }

			}
		}
		succeeded = true;
	}
	///////////////////////////////////////////////////////////////////////////////

	return 0;
}

