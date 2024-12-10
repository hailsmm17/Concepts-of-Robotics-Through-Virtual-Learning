#include "ros/ros.h"
#include "std_msgs/String.h"
#include "iostream"
#include "termios.h"
#include "unistd.h"

class KeyboardPublisher {
public:
    KeyboardPublisher() {
        pub = n.advertise<std_msgs::String>("keyboard_input", 10);
    }

    void run() {
        char c;
        std_msgs::String msg;
        std::cout << "Moving Around: q w e a s d -> Press 'q' to quit." << std::endl;

        while (ros::ok()) {
            c = getKey();
            if (c == 'q')
            {
            	break;
            }
            msg.data = c;
            pub.publish(msg);
            ROS_INFO("Published key pressed: %c", c);
        }
    }

private:
    ros::NodeHandle n;
    ros::Publisher pub;

    char getKey() { // Function to recognize keyboard keys 
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);        //Save old settings
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);      //Disable buffering
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); //Apply new settings
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //Restore old settings
        return ch;
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "example2_bpub");
    KeyboardPublisher keyboard_publisher;
    keyboard_publisher.run();
    return 0;
}

