#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "std_msgs/Int32.h"

static const std::string OPENCV_WINDOW = "Image Window";
using namespace cv;
using namespace std;

class ImageConverter 
{
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_;
	image_transport::Subscriber image_sub_;
	image_transport::Publisher image_pub_;
	ros::Publisher col_pub;

public:
	ImageConverter()
	: it_(nh_)
	{
		//Subscribe to input video feed and publish output video feed
		image_sub_ = it_.subscribe("/camera/image_raw", 1, &ImageConverter::imageCb, this);
		image_pub_ = it_.advertise("/image_converter/output_video", 1);
		col_pub = nh_.advertise<std_msgs::Int32>("colmsg", 1);
		
		cv::namedWindow(OPENCV_WINDOW);
	}
	
	~ImageConverter()
	{
		cv::destroyWindow(OPENCV_WINDOW);
	}
	
	void imageCb(const sensor_msgs::ImageConstPtr& msg)
	{
		cv_bridge::CvImagePtr cv_ptr;
		try
		{
			cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		}
		catch(cv_bridge::Exception e)
		{
			ROS_ERROR("Cv_bridge expection: %s", e.what());
			return;
		}
		
		if (cv_ptr->image.rows > 250 && cv_ptr->image.cols > 250)
			cv::circle(cv_ptr->image, cv::Point(320,240), 100, CV_RGB(0,0,255));
			
				Vec3b intensity = cv_ptr->image.at<Vec3b>(320,240);
				int blue = intensity.val[0];
				int green = intensity.val[1];
				int red = intensity.val[2];
			
			ROS_INFO("b = %d, g = %d, r = %d\n", blue, green, red);
			std_msgs::Int32 colmsg; //defines colmsg
		
		if (blue < 70 && green < 70 && red > 150)
		{
			ROS_INFO("Red Detected");
			red = 1;
			colmsg.data = 0;
			col_pub.publish(colmsg);
		}
		else if (red < 70 && green < 70 && blue > 150)
		{
			ROS_INFO("Blue Detected");
			blue = 2;
			colmsg.data = 1;
			col_pub.publish(colmsg);
		}
		else if (red < 70 && blue < 70 && green > 150)
		{
			ROS_INFO("Green Detected");
			green = 3;
			colmsg.data = 2;
			col_pub.publish(colmsg);
		}
		else
		{
			ROS_INFO("No Color Detected");
			colmsg.data = 3;
			col_pub.publish(colmsg);
		}
		
		//Update GUI Window
		cv::imshow(OPENCV_WINDOW, cv_ptr->image);
		cv::waitKey(3);
		
		//Output modified video stream
		image_pub_.publish(cv_ptr->toImageMsg());
	}
};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "image_converter");
	ImageConverter ic;
	ros::spin();
	
	return 0;
}
