//
// Created by weitongwu on 19-4-29.
//

#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

void imageCallback(const sensor_msgs::CompressedImageConstPtr& msg)
{
    try
    {
        cv::Mat image = cv::imdecode(cv::Mat(msg->data),1);//convert compressed image data to cv::Mat
//        cv::imshow("view", image);
//        cv::waitKey(10);
        std::stringstream filename;
        filename << msg->header.stamp.sec << "." << msg->header.stamp.nsec << ".jpg";
        cv::imwrite(filename.str(),image);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert to image!");
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rosbag_to_image");
    ros::NodeHandle nh;
    cv::namedWindow("view");
    cv::startWindowThread();
    ros::Subscriber sub = nh.subscribe("/camera/right/image_raw/compressed", 1000 , imageCallback);
    ros::spin();
    cv::destroyWindow("view");
}

