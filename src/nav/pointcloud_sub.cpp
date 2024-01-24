//
// Created by jsy on 22.01.24.
//
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/point_cloud_conversion.h>

using namespace std;
using namespace ros;

ros::Publisher* pc1_pub= nullptr;
ros::Subscriber* pc2_sub= nullptr;
void Callback(const sensor_msgs::PointCloud2 ::ConstPtr& msg)
{
    sensor_msgs::PointCloud clouddata;
    sensor_msgs::convertPointCloud2ToPointCloud(*msg, clouddata);
    pc1_pub->publish(clouddata);

}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "pointcloud_sub");//初始化节点和名称
    ros::NodeHandle h;
    pc1_pub = new ros::Publisher;
    pc2_sub = new ros::Subscriber;
    //loop_rate=new ros::Rate(100);
    *pc2_sub = h.subscribe("velodyne_points", 10, Callback);
    *pc1_pub =h.advertise<sensor_msgs::PointCloud>("velodyne_points_pc1",10);
    while(ros::ok())
    {
        ros::spinOnce();
    }

    delete pc1_pub;
    delete pc2_sub;
    return 0;
}