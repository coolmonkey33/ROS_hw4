//Created by Dominic Peichel
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <ros_homework/MyStr.h>
int counter = 0;
//function to output the recieved data
void callback_receive_topicData(const std_msgs::String& msg)
{ 
    ROS_INFO_STREAM("Message received: " << msg.data << ", " << counter);
    counter++;
}

int main (int argc, char **argv)
{
    //initialize the node handler
    ros::init(argc, argv, "hw2_sub");
    ros::NodeHandle nh;
    //initialize subscriber to get the data from the topic_changed and send it to the function
    ros::Subscriber sub = nh.subscribe("/hw2topic_str_changed", 1000, callback_receive_topicData);
    
    
    //start a loop/thread
    ros::spin();
}

