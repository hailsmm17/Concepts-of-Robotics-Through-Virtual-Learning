#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <std_msgs/Int32.h>

ros::Publisher pub;
geometry_msgs::Twist msg;
int x = 3;

void TeleColor(const std_msgs::Int32::ConstPtr& colmsg)
{
	if (colmsg->data == 0) 
	{
		x = 0;
		ROS_INFO("Stop");
		msg.linear.x = 0;
		msg.angular.z = 0;
		pub.publish(msg);
		ros::spinOnce();
	}
	else if (colmsg->data == 1)
	{
		x = 1;
		ROS_INFO("Turn!");
		msg.linear.x = 0;
		msg.angular.z = 1;
		pub.publish(msg);
		ros::spinOnce();
	}
	else if (colmsg->data == 2)
	{
		x = 2;
		ROS_INFO("Move forward!");
		msg.linear.x = 1;
		msg.angular.z = 0;
		pub.publish(msg);
		ros::spinOnce();
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "example3_move");
	ros::NodeHandle n;
	pub = n.advertise<geometry_msgs::Twist>("/pioneer2dx/cmd_vel", 100);
	ros::Subscriber col_sub = n.subscribe<std_msgs::Int32>("colmsg", 100, &TeleColor);
	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
