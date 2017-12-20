#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "iostream"

int main(int argc, char **argv) {

// initializes ROS commands
  ros::init (argc, argv, "publisher");
  
//name of the node that communicates with the ROS system
  ros::NodeHandle nh;
//inializes publisher and gives it a task
  ros::Publisher pub = nh.advertise<std_msgs::String>("publisher",10);

//set  the number of iterations per second
  ros::Rate loop_rate(5);
//we have to specify namespace for that particular command, in this case it is command string
  std::string word;
  std_msgs::String msg;
//Explain the game
  ROS_INFO("This is a game of words.");
  ROS_INFO("Practice using a keyboard using the following words.");
//start the loop with condition while ROS is OK do
  while(ros::ok())
  {
    //ROS_INFO will display the string on the terminal
    ROS_INFO("Insert your answer: ");
    //cin the string from terminal into word
    std::cin>>word;
    //insert word to std_msgs::String so we can send it over ROS as a message
    msg.data=word;
    //publish the message, i.e. word
    pub.publish(msg);
    //put a loop to sleep until new second starts
    loop_rate.sleep();
  }
  return 0;
}

