#include <ros/ros.h>
#include <std_msgs/String.h>
//created by Dominic Peichel
int main(int argc, char **argv)
{
    //create strings
    ros::init(argc, argv, "hw0string_node");
    ros::NodeHandle nh;
    ROS_INFO("hw0string_node has been started");
    std_msgs::String msg;
    msg.data = "Dominic Peichel";
    //output parts of string
    ROS_INFO_STREAM("My message is: " << msg.data);
    ROS_INFO_STREAM("The length of my message is: " << msg.data.length());
    ROS_INFO_STREAM("The 3rd char in my message is: " << msg.data[2]);
    ROS_INFO_STREAM("The last char in my message is: " << msg.data[msg.data.length() - 1]);

    //Convert the string msg to upper cases
    std_msgs::String capitalMessage;
    capitalMessage.data = "";
    for(int i = 0; i < msg.data.length(); i++)
    {
        capitalMessage.data += toupper(msg.data[i]);
    }
    ROS_INFO_STREAM("My message to upper is: " << capitalMessage.data);

    //Reverse the converted string msg
    std_msgs::String reversedMessage;
    reversedMessage.data = "";
    for(int j = capitalMessage.data.length() - 1; j >= 0; j--)
    {
        reversedMessage.data += capitalMessage.data[j];
    }
    ROS_INFO_STREAM("My message reversed is: " << reversedMessage.data);

}