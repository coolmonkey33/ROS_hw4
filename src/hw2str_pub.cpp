//Created by Dominic Peichel
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <ros_homework/MyStr.h>

int main (int argc, char **argv)
{
    //intialize the node handler
    ros::init(argc, argv, "hw2_pub");
    ros::NodeHandle nh;
    
    //initialize the publisher
    ros::Publisher pub = nh.advertise<ros_homework::MyStr>("/hw2_topic", 10);

    //get and set the frequency from the launch file
    double pub_freq = 1;
    nh.getParam("hw2_topic_pub_freq", pub_freq);
    ros::Rate rate(pub_freq);

    //get the incoming message from the launch file
    std_msgs::String inc_msg;
    inc_msg.data = "";
    nh.getParam("hw2_str", inc_msg.data);

    srand(time(NULL));
    
    //publish the combined string
    while (ros::ok()) {
        rate.sleep(); // sleep first not to loose the 1st message
        ros_homework::MyStr msg;
        msg.data = inc_msg.data;
        
        int new_command = rand() % 3;
        msg.command = new_command;
        pub.publish(msg); 
    }
}
