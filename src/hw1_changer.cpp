//Created by Dominic Peichel
#include <ros/ros.h>
#include <std_msgs/String.h>

//create the publisher
ros::Publisher pub;

//function to put a blank into a string and then publish the string
void callback_func_name(const std_msgs::String& msg)
{
    //get the string from the topic
    std_msgs::String new_msg;
    new_msg.data = msg.data;
    //get a random location within the string
    int blank_loc = rand() % (int)(new_msg.data.length());

    //put a blank at the random location
    new_msg.data[blank_loc] = ' ';

    //publish the new string
    pub.publish(new_msg);
}

int main (int argc, char **argv)
{
    //initialize the node handler
    ros::init(argc,argv, "hw1_changer");
    ros::NodeHandle nh;

    //Seed the random number
    srand(time(NULL));

    

    //send the string from the topic to the function and then start the publisher
    ros::Subscriber sub = nh.subscribe("/hw1_topic", 1000, callback_func_name);
    pub = nh.advertise<std_msgs::String>("/hw1_topic_changed", 10);
    //start a loop/thread
    ros::spin();
}