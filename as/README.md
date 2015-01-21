# as

Your description goes here

This "as" package is simply standing for "action server".

There is a pelvis position action server defined in ppas.cpp.

Now action clients who would talk to action servers for pelvis position and 
joint trajectory behavior are also included in this package, which are defined 
in ppac.cpp and they also required action servers to finish their goals at the same 
time.

For testing this code, I just assumed the goal of pelvis height(0.8) and 7d vector contained
6 arm joints comments(all 0) and 1 utorso joint comment(0.5) in ppac.cpp. For integrating this 
program with the whole project, the pelvis height and 7d vector should come from 
planning program.

If you want to run this "as" program independently, please follow steps below
1. roslaunch hku_worlds atlas_v3_sandia_hands.launch (a world just contained Atlas, which will let your computer run faster)
2. rosrun sim_controller USER, then roslaunch fc_bringup sim_task_4.launch 
3. rosrun example_filter foot_wrench_filter_node (for balance)
4. rosrun jacobian_publisher jacobian_publisher (for balance)
5. rosrun as ppas
6. rosrun as ppac

## Example usage

## Running tests/demos
    