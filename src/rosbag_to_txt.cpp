//
// Created by weitongwu on 2019/12/22.
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
    filepath << i << ".txt" ;
    ofstream out(filepath.str());
    for (int j = 0; j < pointcloud.points.size() ; ++j) {
        out << pointcloud.points[j].x << " " <<  pointcloud.points[j].y << " "
        << pointcloud.points[j].z << endl;
    }
    out.close();
    outtime << laserCloudMsg.header.stamp << endl;
    i++;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"rosbag_to_txt");
    ros::NodeHandle nh;
    ros::Subscriber sub;
    sub = nh.subscribe<sensor_msgs::PointCloud2>("/velodyne_points",10, laserCloudHandler);
    ros::spin();
    return 0;
}