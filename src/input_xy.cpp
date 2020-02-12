//Created by Dominic Peichel
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>
#include <stdio.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Bool.h>
#include <thread>
#include <chrono>
using namespace std;


//set up the global variables
ros::Publisher pub;
std_msgs::Bool inc_msg;

void sub_func(const std_msgs::Bool& msg)//function for the subscriber to enable/disable output
{
    inc_msg.data = msg.data;
}

void main_func() //function for inputing target points and publishing them to the goal topic
{
    while(ros::ok()){
        //if the incoming message is true stop the input
        if(inc_msg.data != true)
        {
            //input the target x and y positions
            double targetX = 0;
            double targetY = 0;
            cout << "Input the target X position: ";
            cin >> targetX;
            cout << "Input the target Y position: ";
            cin >> targetY;

            //create a targetpoint variable
            geometry_msgs::Point targetPoint;

            //limit the input to make sure the point is on the screen
            if(targetX >= 11)
            {
                targetX = 11;
            }
            else if(targetX < 0.4)
            {
                targetX = 0.4;
            }
            if(targetY >= 11)
            {
                targetY = 11;
            }
            else if(targetY < .4)
            {
                targetY = .4;
            }
            //publish the target point
            targetPoint.x = targetX;
            targetPoint.y = targetY;
            pub.publish(targetPoint);
            
        }
        //sleep for 1 second to make sure the code has time to update
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ros::spinOnce();
    }
    

    
}

int main (int argc, char **argv)
{
    //set up the publishers and subscribers and start the main function
    ros::init(argc, argv, "input_xy");
    ros::NodeHandle nh;
    ros::Subscriber return_sub = nh.subscribe("/hw4_return",1000,sub_func);
    pub = nh.advertise<geometry_msgs::Point>("/goal", 10);
    main_func();
    ros::spin();
}