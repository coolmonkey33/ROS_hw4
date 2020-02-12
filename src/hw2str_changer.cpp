//Created by Dominic Peichel
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <ros_homework/MyStr.h>

//create the publisher
ros::Publisher pub;

//function to put a blank into a string and then publish the string
void callback_func_name(const ros_homework::MyStr& msg)
{
    //get the string from the topic
    std_msgs::String new_msg;
    new_msg.data = msg.data;
    
    if(msg.command == 0)
    {
        //publish the string as is, aka do nothing
    }
    else if(msg.command == 1)
    {
        //publish the string all upper case
        for(int i = 0; i < new_msg.data.length(); i++)
        {
            new_msg.data[i] = toupper(new_msg.data[i]);
        }
    }
    else if(msg.command == 2)
    {
        //publish the string backwards
        std_msgs::String temp_msg;
        temp_msg.data = "";
        for(int i = new_msg.data.length() - 1; i >= 0; i--)
        {
            temp_msg.data += new_msg.data[i];
        }
        new_msg.data = temp_msg.data;
    }
    else{}

    //publish the new string
    pub.publish(new_msg);
}

int main (int argc, char **argv)
{
    //initialize the node handler
    ros::init(argc,argv, "hw2_changer");
    ros::NodeHandle nh;

    //send the string from the topic to the function and then start the publisher
    ros::Subscriber sub = nh.subscribe("/hw2_topic", 1000, callback_func_name);
    pub = nh.advertise<std_msgs::String>("/hw2topic_str_changed", 10);

    //start a loop/thread
    ros::spin();
}