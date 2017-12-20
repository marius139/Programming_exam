#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "iostream"

int main(int argc, char **argv) {
  ros::init (argc, argv, "publisher");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<std_msgs::String>("publisher",10);
  ros::Rate loop_rate(5);

  std::string word;
  std_msgs::String msg;

  ROS_INFO("This is a game of words.");
  ROS_INFO("Practice using a keyboard using the following words.");

  //start the loop for the game
  while(ros::ok())
  {
    ROS_INFO("Insert your answer: ");
  
    std::cin>>word;
    msg.data=word;

    pub.publish(msg);
 
    loop_rate.sleep();
  }
  return 0;
}
