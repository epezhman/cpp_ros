#include "ros/ros.h"
#include <moveit/move_group_interface/move_group.h>
#include <geometry_msgs/PoseStamped.h>



using namespace std;

int main(int argc, char *argv[]) {

    ros::init(argc, argv, "arm");
    sleep(5.0);
    ROS_INFO("hello from node 2");

    moveit::planning_interface::MoveGroup group("source");
    geometry_msgs::PoseStamped source_pose1;
    source_pose1.header.frame_id = "black_box";

    source_pose1.pose.orientation.w = 0.001;
    source_pose1.pose.orientation.x = -0.707;

    source_pose1.pose.orientation.y = 0.707;

    source_pose1.pose.orientation.z = -0.001;

    source_pose1.pose.position.x = 1.071;
    source_pose1.pose.position.y = 0.025;
    source_pose1.pose.position.z = 0.462;

    group.setPoseTarget(source_pose1, "source_ee");

    moveit::planning_interface::MoveGroup::Plan my_plan;

    bool success = group.plan(my_plan);

    ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

    sleep(5.0);

    if (success) {
        group.execute(my_plan);
    }
    ros::spin(); // wait to die
}