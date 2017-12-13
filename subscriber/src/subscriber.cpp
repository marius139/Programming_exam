#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "iostream"
#include "string"
#include "vector"
#include "time.h"

class Exam
{
  //Initialize variables
  ros::NodeHandle nh;
  ros::Subscriber sub;
  std::string word;
  std::vector<std::string> wordList;
  int chosenPos;
  std::string chosenWord;
  int iRand;
  int arrSize;

private:
void question(){
  //Initialize a random number dependent on time
  srand(time(NULL));
  iRand = rand() % wordList.size();
  chosenPos = 0;
  //Pick a word depending on the entry of the vector
  chosenWord = wordList[iRand];
  //Print this word to the terminal
  ROS_INFO_STREAM(chosenWord);
  //Erase the entry, so that the same word will not be used multiple times in a sequence
  wordList.erase(wordList.begin() + iRand);
}

  //Compare the word from Publisher, with the word selected from question function
void compare (){
  //If the words are similar, then the value of .compare is 0 (The following 6 lines have been correct with an if-else statement)
    while(word.compare(chosenWord) != 0){
      ROS_INFO("Wrong");
      ROS_INFO_STREAM(chosenWord);
      sbCallback(); //Issue when building comes from here
    }
    ROS_INFO("Correct");
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
    arrSize=5;
  //  wordList.push_back("toast");
    wordList.push_back("toast");
    wordList.push_back("beers");
    wordList.push_back("trees");
    wordList.push_back("bees");
    wordList.push_back("fees");
    question();

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
