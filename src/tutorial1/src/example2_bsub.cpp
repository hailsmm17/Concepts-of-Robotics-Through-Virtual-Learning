#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

ros::Publisher pub;

void keyboardCallback(const std_msgs::String::ConstPtr& s_msg) {
    char key = s_msg->data[0];
    ROS_INFO("Subscribed key press: %c", key);

    geometry_msgs::Twist msg;
    
    //Defines the specific movement per key 
    switch (key) {
        case 'w':
            msg.linear.x = 0.3;
            msg.angular.z = 0.0;
            ROS_INFO("Moving forward");
            break;
        case 's':
            msg.linear.x = -0.3;
            msg.angular.z = 0.0;
            ROS_INFO("Moving backward");
            break;
        case 'a': 
            msg.linear.x = 0.0;
            msg.angular.z = 1.0;
            ROS_INFO("Turning left");
            break;
        case 'd': 
            msg.linear.x = 0.0;
            msg.angular.z = -1.0;
            ROS_INFO("Turning right");
            break;
        case 'e': 
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
            ROS_INFO("Stopping");
            break;
        default:
            ROS_INFO("Not applicable key stroke");
            return; // Exit without publishing if key not mapped
    }

    pub.publish(msg);    //Publishes the cmd_vel messages
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "example2_bsub");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);

    ros::Subscriber sub = n.subscribe("keyboard_input", 10, keyboardCallback); //subscriber for keyboard input

    pub = n.advertise<geometry_msgs::Twist>("/pioneer2dx/cmd_vel", 10); //sends movement to robot

    ros::spin(); //keeps programming running for publisher
    return 0;
}

