//
// Created by weitongwu on 2019/12/24.
//

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc,argv,"display_pointcloudmaps_using_rviz");
    ros::NodeHandle nh;
    ros::Publisher pubMapcloud;
    pubMapcloud = nh.advertise<sensor_msgs::PointCloud2>("/laser_cloud_map", 100);
    std::string mapPath = "XXXX.pcd";
    pcl::PointCloud<pcl::PointXYZI>::Ptr mapCloud(new pcl::PointCloud<pcl::PointXYZI>());
    if (pcl::io::loadPLYFile(mapPath, *mapCloud)) {
        std::cerr << "failed to load " << mapPath << std::endl;
        return 0;
    }
    sensor_msgs::PointCloud2 laserCloudSurround;
    pcl::toROSMsg(*mapCloud, laserCloudSurround);
    laserCloudSurround.header.frame_id = "/base_link";
    pubMapcloud.publish(laserCloudSurround);

    ros::spin();
    return 0;
}