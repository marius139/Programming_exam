#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "iostream"
#include "string"
#include "vector"

class Exam
{
  ros::NodeHandle nh;
  ros::Subscriber sub;
  std::string word;
  std::vector<std::string> wordList;
  int chosenPos;
  std::string chosenWord;

private:
void question(){
  chosenPos = 0;
  chosenWord = wordList[chosenPos];
  ROS_INFO_STREAM(chosenWord);
}

void compare (){
    if(word.compare(chosenWord) != 0){
      ROS_INFO_STREAM("Wrong");
    }
    else{
      ROS_INFO_STREAM("Correct");
    }
    question();
}

void sbCallback (const std_msgs::String::ConstPtr& msg){
  //insert data from message into word string
  word=msg->data;
  //output word onto the terminal
  ROS_INFO_STREAM(word);
  compare();
}

public:
  //Exam constructor
  Exam()
  {
    wordList.push_back("toast");
    question();
    //wordList[] = {"toast", "beers", "trees"};
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
