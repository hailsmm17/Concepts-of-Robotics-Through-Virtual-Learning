#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <std_msgs/Int32.h>
#include "ca_msgs/Bumper.h"

geometry_msgs::Twist msg;
ros::Publisher pub;
int x = 3;
int timer_left = 0;
int timer_right = 0;
int left;
int right;

void teleBump(const ca_msgs::Bumper::ConstPtr& bump)
{
//must have roslaunch ca_driver create_2.launch on to work
if (bump->is_right_pressed == 1)
{ right =1; }

if (bump->is_left_pressed == 1)
{ left = 1; }

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "teleopJoy");
	ros::NodeHandle n;
	pub = n.advertise<geometry_msgs::Twist>("/pioneer2dx/cmd_vel", 100);
	ros::Subscriber sub = n.subscribe<ca_msgs::Bumper>("bumper", 1, teleBump);
	ros::Rate loop_rate(10);
	
	while(ros::ok())
	{
		if (x == 3 && left == 0 && right == 0)
		{
			msg.linear.x = 1;
			msg.angular.z = 0;
			pub.publish(msg);
		}
		
		if (left == 1)
		{
			if (timer_left < 10)
			{
				msg.linear.x = -1.0;
				msg.angular.z = 0;
				pub.publish(msg);
			}
			if (timer_left >= 10 && timer_left < 20)
			{
				msg.linear.x = 0;
				msg.angular.z = -1.0;
				pub.publish(msg);
			}
			if (timer_left >= 20)
			{
				timer_left = 0;
				left = 0;
			}
		timer_left++;
		}
		
		if (right == 1)
		{
			if (timer_right < 10)
			{
				msg.linear.x = -1.0;
				msg.angular.z = 0;
				pub.publish(msg);
			}
			if (timer_right >= 10 && timer_right < 20)
			{
				msg.linear.x = 0;
				msg.angular.z = 1.0;
				pub.publish(msg);
			}
			if (timer_right > 20)
			{
				timer_right = 0;
				right = 0;
			}
		timer_right++;
		}
	ros::spinOnce();
	loop_rate.sleep();
	}
return 0;
}
