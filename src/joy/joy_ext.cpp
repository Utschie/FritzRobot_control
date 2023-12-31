#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
using namespace std;
using namespace ros;

ros::Publisher* cmd_pub= nullptr;
ros::Subscriber* joy_sub= nullptr;
static int enable_button;
void joy_extCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
        if ((msg->axes[6]!=0.) || (msg->axes[7]!=0.))
        {
            geometry_msgs::Twist data;
            data.linear.x = msg->axes[7]*0.7;
            data.linear.y = msg->axes[6]*0.7;
            cmd_pub->publish(data);
        }
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "joy_ext");//初始化节点和名称
    ros::NodeHandle h;
    ROS_INFO("Joystick control started.");
    std::string subscribe_topic_joy;
    std::string publish_topic_cmd_vel;
    h.getParam("joystick_topic",subscribe_topic_joy);
    h.getParam("cmd_vel_topic",publish_topic_cmd_vel);
    h.getParam("teleop_twist_joy/enable_button",enable_button);
    cmd_pub = new ros::Publisher;
    joy_sub = new ros::Subscriber;
    //loop_rate=new ros::Rate(100);
    *joy_sub = h.subscribe("joy", 10, joy_extCallback);
    *cmd_pub =h.advertise<geometry_msgs::Twist>("cmd_vel",10);
    while(ros::ok())
    {
        ros::spinOnce();
    }

    delete cmd_pub;
    delete joy_sub;
    return 0;
}