#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "example1_a");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("pioneer2dx/cmd_vel", 10);
	ros::Rate loop_rate(10);
	
	int timer = 0;
	
	while (ros::ok()) 
	{
		geometry_msgs::Twist msg;
		
		if (timer < 100) 
		{
			msg.linear.x = 0.2;
			msg.angular.z = 0;
			
		}
		if (timer >= 100 && timer < 110) 
		{
			msg.linear.x = 0;
			msg.angular.z = 0;
		}
		if (timer >= 110 && timer < 130) 
		{
			msg.linear.x = 0.0;
			msg.angular.z = -3.1;
		}
		if (timer >= 130 && timer < 141) 
		{
			msg.linear.x = 0;
			msg.angular.z = 0;
		}
		if (timer >= 141 && timer < 500) 
		{
			msg.linear.x = 0.57;
			msg.angular.z = 0;
		}
		
		//ROS_INFO("Moving Pioneer2dx");
		pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
		timer++;
	}
	return 0;
} 
