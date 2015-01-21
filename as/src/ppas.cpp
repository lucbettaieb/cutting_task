#include<ros/ros.h>
#include <actionlib/server/simple_action_server.h>
//the following #include refers to the "action" message defined for this package
// The action message can be found in: .../as/action/action.action
// Automated header generation creates multiple headers for message I/O
// These are referred to by the root name (action) and appended name (Action)
#include<as/ppAction.h>
#include <jacobian_publisher/jacobian_publisher.h>
#include <hku_msgs/lowLevelJointController.h>

#include <geometry_msgs/WrenchStamped.h>

#include <Eigen/Eigen>

#include <math.h>
#include <ros/package.h>
#include <yaml-cpp/yaml.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainjnttojacsolver.hpp>
#include <kdl/tree.hpp>

#include <lljc/register.h>
#include <lljc/activate.h>
#include <low_level_joint_controller/low_level_controller_last_command.h>

#include <atlas_msgs/AtlasState.h>
#include <atlas_msgs/AtlasCommand.h>

int g_count = 0;
bool count_failure = false;
using namespace std;
double rate = 100;
double net_my;
#define KV 0.0004//0.0004 //0.0002  //NEED TO TUNE THIS GAIN: how fast to move pelvis in response to my error

//const int NJoints = 28; // already included
double g_atlasState[NJoints];
Eigen::Vector3d g_rfoot_wrench, g_lfoot_wrench;
Eigen::MatrixXd g_J_rhand, g_J_lhand, g_J_rfoot, g_J_lfoot;
Eigen::VectorXd g_x_rhand, g_x_lhand, g_x_rfoot, g_x_lfoot;
Eigen::VectorXd g_limitMin, g_limitMax;
Eigen::VectorXd g_q_rhand, g_q_lhand, g_q_rfoot, g_q_lfoot;
hku_msgs::lowLevelJointController g_command; //Create command msgs
Eigen::VectorXd g_lljcLastCommandJointAngles(28);
ros::Publisher g_pubJointCmd;
Eigen::VectorXd dq_rleg, dq_lleg, dq_rarm, dq_larm, dq_body;
Eigen::VectorXd twist_des;
Eigen::VectorXd q_body_cmd;

class ppActionServer {
private:

    ros::NodeHandle nh_; // we'll need a node handle; get one upon instantiation

    // this class will own a "SimpleActionServer" called "as_".
    // it will communicate using messages defined in as/action/pp.action
    // the type "ppAction" is auto-generated from our name "action" and generic name "Action"
    actionlib::SimpleActionServer<as::ppAction> as_;

    // here are some message types to communicate with our client(s)
    as::ppGoal goal_; // goal message, received from client
    as::ppResult result_; // put results here, to be sent back to the client when done w/ goal
    as::ppFeedback feedback_; // not used in this pp;
    // would need to use: as_.publishFeedback(feedback_); to send incremental feedback to the client

public:
    ppActionServer(); //define the body of the constructor outside of class definition

    ~ppActionServer(void) {
    }
    // Action Interface
    void executeCB(
            const actionlib::SimpleActionServer<as::ppAction>::GoalConstPtr& goal);
};

void lljcLastCommandCB(const hku_msgs::lowLevelJointController& lljc_last_cmd) {
    for (int i = 0; i < NJoints; i++) {
        g_lljcLastCommandJointAngles(i) = lljc_last_cmd.jntAngles[i];
    }
}

void stateListenerCB(const atlas_msgs::AtlasState::ConstPtr &state) {
    for (int i = 0; i < NJoints; i++)
        g_atlasState[i] = state->position[i];
}

void rfootFiltCB(const geometry_msgs::WrenchStamped &rfoot_filt_msg) {
    // copy these values to global var; only 3 of 6 components are non-zero

    g_rfoot_wrench(0) = rfoot_filt_msg.wrench.torque.x; //mx
    g_rfoot_wrench(1) = rfoot_filt_msg.wrench.torque.y; //my
    g_rfoot_wrench(2) = rfoot_filt_msg.wrench.force.z; //fz
}

void lfootFiltCB(const geometry_msgs::WrenchStamped &lfoot_filt_msg) {
    // copy these values to global var; only 3 of 6 components are non-zero

    g_lfoot_wrench(0) = lfoot_filt_msg.wrench.torque.x;
    g_lfoot_wrench(1) = lfoot_filt_msg.wrench.torque.y;
    g_lfoot_wrench(2) = lfoot_filt_msg.wrench.force.z;
}

void rhandJacobianListenerCB(
        const jacobian_publisher::Jacobian::ConstPtr &jac) {
    // g_J_rhand is a 6xn matrix where n is the number of joints in chain (root to tip).
    // q_x is a 6x1 vector (x, y, z, roll, pitch, yaw).
    MessageToJacobian(*jac, g_J_rhand, g_x_rhand);
}

void lhandJacobianListenerCB(
        const jacobian_publisher::Jacobian::ConstPtr &jac) {
    // g_J_rhand is a 6xn matrix where n is the number of joints in chain (root to tip).
    // q_x is a 6x1 vector (x, y, z, roll, pitch, yaw).
    MessageToJacobian(*jac, g_J_lhand, g_x_lhand);
}

void rfootJacobianListenerCB(
        const jacobian_publisher::Jacobian::ConstPtr &jac) {
    // g_J is a 6xn matrix where n is the number of joints in chain (root to tip).
    // q_x is a 6x1 vector (x, y, z, roll, pitch, yaw).
    MessageToJacobian(*jac, g_J_rfoot, g_x_rfoot);
}

void lfootJacobianListenerCB(
        const jacobian_publisher::Jacobian::ConstPtr &jac) {
    // g_J is a 6xn matrix where n is the number of joints in chain (root to tip).
    // q_x is a 6x1 vector (x, y, z, roll, pitch, yaw).
    MessageToJacobian(*jac, g_J_lfoot, g_x_lfoot);
}

/**
 * \brief Creates a joint index map between the chain joints and the 28 Atlas joints and loads joint limits from a configuration file
 * \param jointMap_ Returned map
 * \param chain Input chain to compute map for
 * \return 0 if successful, -1 if loading joint limits failed, >0 id of the joint that could not be found (+1)
 */
int GetJointMap(std::vector<std::string> &jointNames) //std::vector< int >& jointMap_, KDL::Chain& chain)
{
    //std::vector<std::string> jointNames(NJoints); // Joint names (in the order of Atlas joints, this should come from a config file or a header file)
    jointNames[0] = "back_bkz";
    jointNames[1] = "back_bky";
    jointNames[2] = "back_bkx";
    jointNames[3] = "neck_ry";
    jointNames[4] = "l_leg_hpz";
    jointNames[5] = "l_leg_hpx";
    jointNames[6] = "l_leg_hpy";
    jointNames[7] = "l_leg_kny";
    jointNames[8] = "l_leg_aky";
    jointNames[9] = "l_leg_akx";
    jointNames[10] = "r_leg_hpz";
    jointNames[11] = "r_leg_hpx";
    jointNames[12] = "r_leg_hpy";
    jointNames[13] = "r_leg_kny";
    jointNames[14] = "r_leg_aky";
    jointNames[15] = "r_leg_akx";
    jointNames[16] = "l_arm_shy";
    jointNames[17] = "l_arm_shx";
    jointNames[18] = "l_arm_ely";
    jointNames[19] = "l_arm_elx";
    jointNames[20] = "l_arm_wry";
    jointNames[21] = "l_arm_wrx";
    jointNames[22] = "r_arm_shy";
    jointNames[23] = "r_arm_shx";
    jointNames[24] = "r_arm_ely";
    jointNames[25] = "r_arm_elx";
    jointNames[26] = "r_arm_wry";
    jointNames[27] = "r_arm_wrx";

    std::string limitsFile = ros::package::getPath("hku_configs")
            + "/config/joint_limits.yaml";

    YAML::Node config = YAML::LoadFile(limitsFile);
    if (!config["joint_limits"]) {
        ROS_ERROR("Failed to load joint limits from file: %s",
                limitsFile.c_str());
        return -1;
    } else {
        ROS_INFO("loaded joint limits");
        for (int i = 0; i < (int) jointNames.size(); i++) {
            // hack: squeeze the joint limits, or expand the joint limits;
            // e.g., useful to prevent commands out of range, or useful to tolerate some overrun; user must decide this...
            g_limitMin(i) =
                    config["joint_limits"][jointNames[i].c_str()]["min_position"].as<
                    double>() - 0.05; //+0.005;
            g_limitMax(i) =
                    config["joint_limits"][jointNames[i].c_str()]["max_position"].as<
                    double>() + 0.05; //-0.005;
        }

        std::cout << "limitMin: " << g_limitMin.transpose() << std::endl;
        std::cout << "limitMax: " << g_limitMax.transpose() << std::endl;
        return 0;
    }
}

// This function is specialized to assume reference frame is the pelvis! (consistent with Jacobian publisher)

void set_q_limbs_from_state(void) {
    // extract joint values from atlas state to fill limb vectors in KDL order--counting from 0 at pelvis for each limb
    // torso:
    for (int i = 0; i < 3; i++) {
        g_q_rhand(i) = g_atlasState[i];
        g_q_lhand(i) = g_atlasState[i];
    }
    //arms:
    for (int i = 3; i < 9; i++) {
        g_q_rhand(i) = g_atlasState[i + 19];
        g_q_lhand(i) = g_atlasState[i + 13];
    }
    //legs:
    for (int i = 0; i < 6; i++) {
        g_q_lfoot(i) = g_atlasState[i + 4];
        g_q_rfoot(i) = g_atlasState[i + 10];
    }

}

// feed in separate vectors for limbs, and stuff these into equivalent whole-body vector;
// return the result in q_body

void set_q_body_from_q_limbs(Eigen::VectorXd q_rhand, Eigen::VectorXd q_lhand,
        Eigen::VectorXd q_rfoot, Eigen::VectorXd q_lfoot,
        Eigen::VectorXd &q_body) {
    // extract joint values from atlas state to fill limb vectors in KDL order--counting from 0 at pelvis for each limb
    // torso:

    for (int i = 0; i < 3; i++) {
        q_body(i) = q_rhand(i);
    }
    //arms:
    for (int i = 3; i < 9; i++) {
        q_body(i + 19) = q_rhand(i);
        q_body(i + 13) = q_lhand(i);
    }
    //legs:
    for (int i = 0; i < 6; i++) {
        q_body(i + 4) = q_lfoot(i);
        q_body(i + 10) = q_rfoot(i);
    }

}

//function to return if a proposed whole-body qvec is within the joint-range limits
// fix this--starting up at joint limit returns "false"
// manual hack adds magic number for tolerance

bool q_in_range(Eigen::VectorXd qvec, Eigen::VectorXi &in_range) {
    bool safe = true;
    //bool in_range = true;
    for (int i = 0; i < NJoints; i++) {
        in_range(i) = 1;
        if (qvec(i) < g_limitMin(i)) {
            safe = false;
            in_range(i) = 0;
        }
        if (qvec(i) > g_limitMax(i)) {
            safe = false;
            in_range(i) = 0;
        }
    }
    // if survive to here, then all is well
    return safe;
}

//implementation of the constructor:
// member initialization list describes how to initialize member as_
// member as_ will get instantiated with specified node-handle, name by which this server will be known,
//  a pointer to the function to be executed upon receipt of a goal.
//
// Syntax of naming the function to be invoked: get a pointer to the function, called executeCB, which is a member method
// of our class ppActionServer.  Since this is a class method, we need to tell boost::bind that it is a class member,
// using the "this" keyword.  the _1 argument says that our executeCB takes one argument
// the final argument  "false" says don't start the server yet.  (We'll do this in the constructor)

ppActionServer::ppActionServer() :
as_(nh_, "pelvis_position_action",
boost::bind(&ppActionServer::executeCB, this, _1), false)
// in the above initialization, we name the server "pelvis_position_action"
//  clients will need to refer to this name to connect with this server
{
    ROS_INFO("in constructor of ppActionServer...");
    // do any other desired initializations here...specific to your implementation

    as_.start(); //start the server running
}

//executeCB implementation: this is a member method that will get registered with the action server
// argument type is very long.  Meaning:
// actionlib is the package for action servers
// SimpleActionServer is a templated class in this package (defined in the "actionlib" ROS package)
// <as::ppAction> customizes the simple action server to use our own "action" message
// defined in our package, "as", in the subdirectory "action", called "pp.action"
// The name "action" is prepended to other message types created automatically during compilation.
// e.g.,  "ppAction" is auto-generated from (our) base name "action" and generic name "Action"

void ppActionServer::executeCB(
        const actionlib::SimpleActionServer<as::ppAction>::GoalConstPtr& goal) {
    ros::Rate CBlooprate(rate);
    //ROS_INFO("in executeCB");

    while (abs(goal->height - (-g_x_rfoot(2) + 0.05)) > 0.01) {
        twist_des(2) = -(goal->height - (-g_x_rfoot(2) + 0.05)); // let the pelvis move in vertical direction 
        //in response to the difference between the target height and current height of pelvis
        ROS_INFO("Current height of pelvis: %f", -g_x_rfoot(2) + 0.01);
        double diff_my;
        diff_my = net_my + 17;
        twist_des(0) = -KV*diff_my;// let the pelvis move horizontally for keeping balance 
        // NEED TO TUNE KV
        //here's a strategy: command incremental angles to produce desired twist*dt
        // compute these separately for right foot and left foot, relative to pelvis
        dq_rleg = g_J_rfoot.inverse() * twist_des * (1.0 / (rate * (goal->duration-1.4)));//need to -1.4 second on the moving time
        //for letting pelvis and arm movement finish at the same time, don't know why 
        dq_lleg = g_J_lfoot.inverse() * twist_des * (1.0 / (rate * (goal->duration-1.4)));

        // get the current angles:
        set_q_body_from_q_limbs(dq_rarm, dq_larm, dq_rleg, dq_lleg, dq_body);
        //increment the leg joints, per the above plan
        // NOTE: there are important differences incrementing commanded angles relative to actual angles vs planned angles
        q_body_cmd += dq_body;
        // put these angle commands in lljc message and ship it out
        for (int i = 0; i < NJoints; i++) {
            g_command.jntAngles[i] = q_body_cmd(i);
        }
        g_pubJointCmd.publish(g_command);
        CBlooprate.sleep(); //whew!  that was tiring.  Let's take a quick nap...
        ros::spinOnce();
    }
    result_.height = -g_x_rfoot(2) + 0.05;
    as_.setSucceeded(result_);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "action_server"); // name this node

    ROS_INFO("instantiating the action action server: ");

    ppActionServer as; // just create an instance of the class "ppActionServer", never use "as" in this program 

    ros::start();
    ros::Rate looprate(rate);
    Eigen::VectorXd q_position = Eigen::VectorXd::Zero(NJoints);
    Eigen::VectorXd q_velocity = Eigen::VectorXd::Zero(NJoints);

    twist_des = Eigen::VectorXd::Zero(6, 1);
    dq_rleg = Eigen::VectorXd::Zero(6, 1);
    dq_lleg = Eigen::VectorXd::Zero(6, 1);
    dq_rarm = Eigen::VectorXd::Zero(9, 1);
    dq_larm = Eigen::VectorXd::Zero(9, 1);
    dq_body = Eigen::VectorXd::Zero(28, 1);
    q_body_cmd = Eigen::VectorXd::Zero(28, 1);

    // Subscribe to state and Jacobian topics, for pelvis control
    g_atlasState[0] = 1e100;
    ros::NodeHandle* nodeHandle = new ros::NodeHandle();
    ros::Subscriber subJointStates = nodeHandle->subscribe("/atlas/atlas_state",
            1, stateListenerCB);
    ros::Subscriber subJacobian_rhand = nodeHandle->subscribe(
            "/atlas/Jacobians/pelvis2r_hand", 1, rhandJacobianListenerCB);
    ros::Subscriber subJacobian_lhand = nodeHandle->subscribe(
            "/atlas/Jacobians/pelvis2l_hand", 1, lhandJacobianListenerCB);
    ros::Subscriber subJacobian_rleg = nodeHandle->subscribe(
            "/atlas/Jacobians/pelvis2r_foot", 1, rfootJacobianListenerCB);
    ros::Subscriber subJacobian_lleg = nodeHandle->subscribe(
            "/atlas/Jacobians/pelvis2l_foot", 1, lfootJacobianListenerCB);
    ros::Subscriber sub_lljc = nodeHandle->subscribe("/lljc/last_cmd", 1,
            lljcLastCommandCB);

    //pubLfootFiltered = n.advertise<geometry_msgs::WrenchStamped>("/l_foot_filtered", 1, true);
    ros::Subscriber sub_rfoot_filt = nodeHandle->subscribe("/r_foot_filtered",
            1, rfootFiltCB);
    ros::Subscriber sub_lfoot_filt = nodeHandle->subscribe("/l_foot_filtered",
            1, lfootFiltCB);

    g_limitMin = Eigen::VectorXd::Zero(28, 1);
    g_limitMax = Eigen::VectorXd::Zero(28, 1);
    Eigen::VectorXi in_range(NJoints);
    std::vector < std::string > jointNames(NJoints);
    if (GetJointMap(jointNames) < 0) { // fill up the min and max joint limit vectors
        return 0;
    };

    ROS_INFO("Waiting for atlas_state topic and Jacobian publications.");
    while (ros::ok()) {
        looprate.sleep();
        ros::spinOnce();
        if (g_atlasState[0] < -10.0 || g_atlasState[0] > 10.0)
            continue;
        if (g_J_rhand.rows() == 0 || g_J_rhand.cols() == 0)
            continue;
        break;
    }

    // here if got Jacobian, so size corresponding vectors for limbs
    g_q_rhand = Eigen::VectorXd::Zero(g_J_rhand.cols());
    g_q_lhand = Eigen::VectorXd::Zero(g_J_lhand.cols());
    g_q_rfoot = Eigen::VectorXd::Zero(g_J_rfoot.cols());
    g_q_lfoot = Eigen::VectorXd::Zero(g_J_lfoot.cols());

    net_my = 0;
    net_my = g_rfoot_wrench(1) + g_lfoot_wrench(1);
    ROS_INFO("net angle torque about y: %f", net_my);

    ROS_INFO("waiting for lljc last command: ");
    g_lljcLastCommandJointAngles(0) = 1000.0;
    //wait for something at least semi-plausible to be published for joint-angle 0.
    while ((g_lljcLastCommandJointAngles(0) < -10.0)
            || (g_lljcLastCommandJointAngles(0) > 10.0)) {
        looprate.sleep();
        ros::spinOnce();
    }
    ROS_INFO("got lljc last command: ");
    //cout << g_lljcLastCommandJointAngles.transpose() << endl;
    q_position = g_lljcLastCommandJointAngles; // start cmd identical to most recent command

    // initiate cmd identical to LLJC last command:
    for (int i = 0; i < NJoints; i++) {
        g_command.jntAngles[i] = q_position(i);
        g_command.jntVelocities[i] = 0.0;
        g_command.jntAccelerations[i] = 0.0;
        g_command.k_effort[i] = 255;
    }

    //low level joint controller: register with LLJC; this is HKU-specific protocol
    bool Joint_select[NJoints];
    for (int i = 4; i < 16; i++)
        Joint_select[i] = true;
    lljc::BehaviorData BD = lljc::register_behavior("jacobian_pp", 1, true,
            Joint_select, Joint_select, Joint_select);
    if (!BD.is_registered) {
        ROS_ERROR("Failed to register with LLJC!!!");
        return 1;
    }

    // Activate required joints with LLJC; i.e., try to take ownership of joints
    ROS_INFO("Activating Joints");
    hku_msgs::BehaviorActData act_data;
    act_data.behavior_name = "jacobian_pp";
    for (int jntInd = 4; jntInd < 16; jntInd++) {
        act_data.joint_select[jntInd] = true; //try taking ALL the joints of legs
    }

    //see if we were successful
    if (lljc::activate_behavior(&act_data))
        ROS_INFO("Activated Joints with LLJC");
    else {
        ROS_FATAL("Failed to activate joints with the LLJC");
        return 0;
    }

    // talk to LLJC by publishing to the named topic, as provided by LLJC upon registration
    g_pubJointCmd = nodeHandle->advertise < hku_msgs::lowLevelJointController
            > (BD.topic, 1);

    if (ros::ok()) {
        // fill q_body_cmd to match the current state:
        set_q_limbs_from_state(); // initialize all limb vectors to current pose
        set_q_body_from_q_limbs(g_q_rhand, g_q_lhand, g_q_rfoot, g_q_lfoot,
                q_body_cmd);
        for (int i = 0; i < NJoints; i++) { //put these values into the command message to send to LLJC
            g_command.jntAngles[i] = q_body_cmd(i);
        }

        // test the LLJC command:
        ROS_INFO("command current pose; robot may droop");
        g_pubJointCmd.publish(g_command);

        ROS_INFO("Current height of pelvis: %f", -g_x_rfoot(2) + 0.05);//0.05 is the height of foot,-g_x_rfoot(2) is the 
        //vertical distance between pelvis and ankle, so the sum is the vertical distance between pelvis and group
        ROS_INFO("going into spin");
        // from here, all the work is done in the action server, with the interesting stuff done within "executeCB()"
        while (ros::ok()) {
            ros::spin();
        }

        return 0;
    }
}

