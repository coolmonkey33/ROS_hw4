//Created by Dominic Peichel
#include <ros/ros.h>
#include <std_msgs/String.h>

int main (int argc, char **argv)
{
    //intialize the node handler
    ros::init(argc, argv, "hw1_pub2");
    ros::NodeHandle nh;
    
    //initialize the publisher
    ros::Publisher pub = nh.advertise<std_msgs::String>("/hw1_topic", 10);

    //get and set the frequency from the launch file
    double pub_freq = 1;
    nh.getParam("hw1_topic_pub_freq", pub_freq);
    ros::Rate rate(pub_freq);

    //get the incoming message from the launch file
    std_msgs::String inc_msg;
    inc_msg.data = "";
    nh.getParam("hw1_str2", inc_msg.data);

    //create a local string to append the launch string to
    std_msgs::String msg;
    msg.data = "MMMMMMM";

    //append the incoming string to the local string
    std_msgs::String comb_msg;
    comb_msg.data = "";
    comb_msg.data = msg.data + inc_msg.data;
    
    //publish the combined string
    while (ros::ok()) {
        rate.sleep(); // sleep first not to loose the 1st message

        pub.publish(comb_msg); 
    }
}
