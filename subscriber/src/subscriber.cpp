#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "iostream"

class Exam
{
  ros::NodeHandle nh;
  ros::Subscriber sub;
  std::string word;

private:
void sbCallback (const std_msgs::String::ConstPtr& msg){
  //insert data from message into word string
  word=msg->data;
  //output word onto the terminal
  ROS_INFO_STREAM(word);
}

public:
  //Exam constructor
  Exam()
  {
  sub = nh.subscribe("publisher", 10, &Exam::sbCallback,this);
  };
//Exam deconstructor
~Exam(){};
};

//we start here
int main(int argc, char **argv) {

  ros::init (argc, argv, "subscriber");
  //create and object "a" of type Exam
  Exam a;
  //initializes all the callbacks for subscriber
  ros::spin();

  return 0;
}
