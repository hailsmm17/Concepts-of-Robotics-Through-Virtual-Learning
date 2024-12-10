#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "stdio.h"
#include "termios.h"


geometry_msgs::Twist msg;
ros::Publisher pub;

int getch() 
{
	//set up termios for non-blocking keyboard input
	static struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt); //save old settings
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO); //disbale buffering
	tcsetattr(STDIN_FILENO, TCSANOW, &newt); //apply new settings
	int c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restore old settings
	return c;
}


void KeyPress() 
{
	char c;
	bool dirty = false;
	geometry_msgs::Twist msg;
	
	double linear_speed = 0.5; //default speed
	double angular_speed = 1.0;
	
	std::cout << "Reading from keyboard, use w,s,a & d keys to operate Pioneer2dx \n";
	std::cout << "Press 'q' to quit \n";
	
		c = getch();
		
		msg.linear.x = 0.0; //Reset
		msg.angular.z = 0.0;
		
		switch(c)
		{
			case 'w': //up
				msg.linear.x = linear_speed;
				dirty = true;
				break;
			case 's': //down
				msg.linear.x = -linear_speed;
				dirty = true;
				break;
			case 'a': //left
				msg.angular.z = angular_speed;
				dirty = true;
				break;
			case 'd': //right
				msg.angular.z = -angular_speed;
				dirty = true;
				break;
			case 'q': //quit
				return;
		}
		
		if (dirty) 
		{
			pub.publish(msg);
			dirty = false;
		}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "example2_a");
	ros::NodeHandle n;
	pub = n.advertise<geometry_msgs::Twist>("pioneer2dx/cmd_vel", 1000);
	void KeyPress();
	//ros::Subscriber sub = n.subscribe("joy", 1000, joystickAnswer);
	ros::Rate loop_rate(10);
	
	while (ros::ok()) 
	{
		ros::spinOnce();//click 1 -> publish 1 
		loop_rate.sleep(); //subscribe value (similar to subscriber)  
	}
	return 0;
}
