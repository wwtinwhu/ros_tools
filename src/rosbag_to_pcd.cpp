//
// Created by weitongwu on 19-6-23.
//

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/pcd_io.h>
#include <fstream>

using namespace std;

int i = 0;

ofstream outtime("time.txt");

void laserCloudHandler(const sensor_msgs::PointCloud2 laserCloudMsg)
{
    pcl::PointCloud<pcl::PointXYZI> pointcloud;
    pcl::fromROSMsg(laserCloudMsg,pointcloud);
    ROS_INFO("%d",pointcloud.points.size());
    std::stringstream filepath;
    filepath << i << ".pcd" ;
    pcl::io::savePCDFileASCII(filepath.str(),pointcloud);
    outtime << laserCloudMsg.header.stamp << endl;
    i++;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"rosbag_to_pcd");
    ros::NodeHandle nh;
    ros::Subscriber sub;
    sub = nh.subscribe<sensor_msgs::PointCloud2>("/velodyne_points",10, laserCloudHandler);
    ros::spin();
    return 0;
}
