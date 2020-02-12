//Created by Dominic Peichel
#include <ros/ros.h>
#include <std_msgs/String.h>

//function to output the recieved data
void callback_receive_topicData(const std_msgs::String& msg)
{ 
    ROS_INFO_STREAM("Message received: " << msg.data);
}

int main (int argc, char **argv)
{
    //initialize the node handler
    ros::init(argc, argv, "hw1_sub");
    ros::NodeHandle nh;
    //initialize subscriber to get the data from the topic_changed and send it to the function
    ros::Subscriber sub = nh.subscribe("/hw1_topic_changed", 1000, callback_receive_topicData);
    //start a loop/thread
    ros::spin();
}

