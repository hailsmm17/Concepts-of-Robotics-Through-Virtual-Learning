#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"

geometry_msgs::Twist msg;
ros::Publisher pub;
int joystick = 0;

void joystickAnswer(const sensor_msgs::Joy::ConstPtr& joy) 
{
	if (joy->axes[1] == 0 && joy->axes[0] == 0) 
	{
		ROS_INFO("No movement");
		joystick = 0;
	}
	else 
	{
		ROS_INFO("Movement");
		joystick = 1;
		msg.linear.x = joy->axes[1];
		msg.angular.z = joy->axes[0];
		ROS_INFO("z Movement = %f, msg.angular.z");
		pub.publish(msg);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "example2");
	ros::NodeHandle n;
	pub = n.advertise<geometry_msgs::Twist>("pioneer2dx/cmd_vel", 1000);
	ros::Subscriber sub = n.subscribe("joy", 1000, joystickAnswer);
	ros::Rate loop_rate(10);
	
	while (ros::ok()) 
	{
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
