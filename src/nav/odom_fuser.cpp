//
// Created by jsy on 23.12.23.
//This node uses imu estimated yaw to replace the yaw from encoders
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TwistStamped.h>
#include <sensor_msgs/Imu.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
using namespace std;
using namespace ros;
using namespace message_filters;
ros::Publisher* odom_pub= nullptr;
ros::Time* current_time= nullptr;
ros::Time* last_time= nullptr;
tf::TransformBroadcaster* odom_broadcaster= nullptr;
double* x= nullptr;
double* y= nullptr;
double* yaw= nullptr;
void Callback(const geometry_msgs::TwistStamped::ConstPtr& vel_msg, const sensor_msgs::Imu::ConstPtr& imu_msg)
{
    double vx = vel_msg->twist.linear.x;
    double vy = vel_msg->twist.linear.y;
    double vth= imu_msg->angular_velocity.z;


    *current_time = ros::Time::now();

    //compute odometry in a typical way given the velocities of the robot
    double dt = (*current_time - *last_time).toSec();
    double delta_x = (vx * cos(*yaw) - vy * sin(*yaw)) * dt;//use current vx,vy and last yaw to estimate the position
    double delta_y = (vx * sin(*yaw) + vy * cos(*yaw)) * dt;

    *x += delta_x;
    *y += delta_y;
    *yaw= tf::getYaw(imu_msg->orientation);//uses ekf estimated yaw

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = imu_msg->orientation;

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = *current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_footprint";

    odom_trans.transform.translation.x = *x;
    odom_trans.transform.translation.y = *y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster->sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = *current_time;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_footprint";

    //set the position
    odom.pose.pose.position.x = *x;
    odom.pose.pose.position.y = *y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;

    //publish the message
    odom_pub->publish(odom);

    *last_time = *current_time;
    ros::Rate loop_rate(50);//设置节点的loop频率
    loop_rate.sleep();
}





int main(int argc, char** argv){
    ros::init(argc, argv, "odom_fuser");
    ros::NodeHandle n;
    odom_pub = new ros::Publisher;
    current_time= new ros::Time;
    last_time= new ros::Time;
    x=new double;
    y=new double;
    yaw= new double;
    odom_broadcaster=new tf::TransformBroadcaster;
    //pose's rate is 50hz, vel's rate is 200hz
    message_filters::Subscriber<geometry_msgs::TwistStamped> vel_sub(n,"chassis/vel",1);
    message_filters::Subscriber<sensor_msgs::Imu> pose_sub(n,"chassis/pose", 1) ;
    typedef sync_policies::ApproximateTime<geometry_msgs::TwistStamped, sensor_msgs::Imu> MySyncPolicy;
    Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), vel_sub, pose_sub);
    sync.registerCallback(boost::bind(&Callback, _1, _2));
    //intialize the variables
    *odom_pub= n.advertise<nav_msgs::Odometry>("odom_fused", 1);
    *current_time= ros::Time::now();
    *last_time= ros::Time::now();
    *x=0.;
    *y=0.;
    *yaw=0.;

    ros::spin();

    delete odom_pub;
    delete current_time;
    delete last_time;
    delete x;
    delete y;
    delete yaw;
    odom_pub=nullptr;
    current_time=nullptr;
    last_time=nullptr;
    x=nullptr;
    y=nullptr;
    yaw=nullptr;

    return 0;
}
