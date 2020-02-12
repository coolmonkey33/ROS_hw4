//Created by Dominic Peichel
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <turtlesim/Pose.h>
#include <std_msgs/Bool.h>
using namespace std;

//initialize global variables
ros::Publisher velocity_pub;
ros::Publisher return_pub;
geometry_msgs::Point currentLoc;


//initiatilze constants
const double LIN_VEL_CONST = 5;
const double ANG_VEL_CONST = 25;
const double PI = 3.14159265359;

void currentLocationSubFunc(const turtlesim::Pose& msg)//function for updating the current location using a subscriber
{
    //set the location equal to the location from the msg
    currentLoc.x = msg.x;
    currentLoc.y = msg.y;
    currentLoc.z = msg.theta;
    //change angles to be from 0 to 2 pi instead of -pi to pi
    if(currentLoc.z < 0)
    {
        currentLoc.z += 2*PI;
    }
}
double calcAngularVel (double abs_target_angle, double current_angle) //function to calculate the Angular velocity using a target angle and the current angle
{
    //make sure the system understands that 0 and 2Pi are the same angle
    if(abs_target_angle < 0.5 && current_angle > PI)
    {
        abs_target_angle = 2*PI;
    }
    else if(abs_target_angle > (2*PI - .5)&& current_angle < PI)
    {
        abs_target_angle = 0;
    }
    //angular velocity calculation
    double angularVel = (abs_target_angle - current_angle);
    angularVel = ANG_VEL_CONST*angularVel;
    return angularVel;
}
double calcAbsTargetAngle(double currentX, double currentY, double targetX, double targetY) //function for calculating the Absolute Target Angle
{
    //find the target angle using inverse tangent 2 which gets a direction from -pi to pi
    double AbsTargetAngle = std::atan2((targetY-currentY),(targetX-currentX));
    //adjust the angle to be from 0 to 2pi
    if(AbsTargetAngle < 0)
    {
        AbsTargetAngle += 2*PI;
    }
    return AbsTargetAngle;
    
}
double calcLinearVel(double currentX, double currentY, double targetX, double targetY) //function to calculate the linear velocity
{
    //calculate the linear velocity using the distance to the target point
    double linearVelocity = LIN_VEL_CONST*std::sqrt(std::pow(targetX-currentX,2)+std::pow(targetY-currentY,2));
    return linearVelocity;
    
}
void goToPosition(double targetX, double targetY) //function to go to a target position
{
    //initialize variables
    geometry_msgs::Twist vel_msg;
	//ros::NodeHandle nh;
    double linear_velocity = 0.0;
    double abs_target_angle = 0.0;
    double angular_velocity = 0.0;
	vel_msg.linear.x = 0;
	vel_msg.linear.y = 0;
	vel_msg.linear.z = 0;
	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;
	vel_msg.angular.z = 0;

    //start a subscriber to get the current position
    

    //send a message to stop the input from being able to send data
    std_msgs::Bool next_data;
    next_data.data = true;
    return_pub.publish(next_data);

    ros::spinOnce();
    
    do {
        //calculate the linear velocity, target angle and angular velocity
        linear_velocity = calcLinearVel(currentLoc.x,currentLoc.y,targetX,targetY);
        abs_target_angle = calcAbsTargetAngle(currentLoc.x,currentLoc.y,targetX,targetY);
        angular_velocity = calcAngularVel(abs_target_angle,currentLoc.z);

        //set the velocity and linear velocity
        vel_msg.linear.x = linear_velocity;
        vel_msg.angular.z = angular_velocity;

        //if the location is on the edge of the screen, make the angular velocity the only part until the turtle can go to it's point
        if(currentLoc.x > 10.9 || currentLoc.x < .3 || currentLoc.y > 10.9 || currentLoc.y < .3)
        {
            //make the program realize 0 and 2pi are the same angle
            if(abs_target_angle < 0.5 && currentLoc.z > PI)
            {
                abs_target_angle = 2*PI;
            }
            else if(abs_target_angle > (2*PI - .5)&& currentLoc.z < PI)
            {
                abs_target_angle = 0;
            }
            //set the linear velocity to 0 if the turtle is on the edge and facing away from the point
            if(abs(abs_target_angle-currentLoc.z) > .5 )
            {
                vel_msg.linear.x = 0;
            }
        }
        //publish the velocity message
		velocity_pub.publish(vel_msg);
        
		ros::spinOnce();
	} while(!(abs(currentLoc.x - targetX) < .1) || !(abs(currentLoc.y - targetY) <.1));

    //stop the turtle from moving and allow the input to send coordinates again
    vel_msg.linear.x = 0;
    vel_msg.angular.z = 0;
	velocity_pub.publish(vel_msg);
    next_data.data = false;
    return_pub.publish(next_data);
    ros::spinOnce();



}


void target_subscriber_function(const geometry_msgs::Point& msg)//function for the subscriber of the input coordinates
{
    
    goToPosition(msg.x,msg.y);
    
}


int main (int argc, char **argv)
{
    //set up the subscribers and publishers
    ros::init(argc, argv, "input_xy");
    ros::NodeHandle nh;
    ros::Subscriber curLocSub; 
    curLocSub = nh.subscribe("/turtle1/pose",1000,currentLocationSubFunc);
    velocity_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    ros::Subscriber sub = nh.subscribe("/goal", 1000, target_subscriber_function);
    return_pub = nh.advertise<std_msgs::Bool>("/hw4_return", 1000);
    

    ros::spin();
}
