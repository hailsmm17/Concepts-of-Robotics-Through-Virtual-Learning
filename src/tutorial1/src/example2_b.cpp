#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

class KeyboardPublisher {
public:
    KeyboardPublisher() {
        // Set up the publisher to publish to the 'keyboard_input' topic
        pub_ = nh_.advertise<std_msgs::String>("keyboard_input", 10);
    }

    void run() {
        char c;
        std_msgs::String msg;
        std::cout << "Press keys to send messages. Press 'q' to quit." << std::endl;

        while (ros::ok()) {
            // Capture a single key press
            c = getKey();
            if (c == 'q') {
                break;
            }
            
            // Publish the key press as a string message
            msg.data = c;
            pub_.publish(msg);
            ROS_INFO("Key pressed: %c", c);
        }
    }

private:
    ros::NodeHandle nh_;
    ros::Publisher pub_;

    // Function to capture a single key press without requiring Enter
    char getKey() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);        // Save old settings
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);      // Disable buffering
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
        return ch;
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "keyboard_publisher");
    KeyboardPublisher keyboard_publisher;
    keyboard_publisher.run();
    return 0;
}

