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
  int counterCorrect=0;
  int counterWrong=0;


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
  //wordList.erase(wordList.begin() + iRand);
}

void sbCallback (const std_msgs::String::ConstPtr& msg){
  //insert data from message into word string
  word=msg->data;
  //output word onto the terminal
  ROS_INFO("You wrote: ");
  ROS_INFO_STREAM(word);
  compare();
}
//Different statements announced dependent on performance
void win_lose(){
//Switchcase for 10 correct answers and less than 10 wrong answers
  if (counterCorrect == 10) {
    switch (counterWrong) {
      case 0:
      ROS_INFO("FANTASTIC!");
      break;
      case 1: case 2: case 3:
      ROS_INFO("You did good");
      break;
      case 4: case 5: case 6:
      ROS_INFO("You did fine");
      break;
      case 7: case 8: case 9:
      ROS_INFO("You participated");
      break;
    }
    ros::shutdown();
  }

//Switchcase for 10 wrong answers and less than 10 correct answers
  if (counterWrong == 10) {
    switch (counterCorrect) {
      case 0:
      ROS_INFO("You suck");
      break;
      case 1: case 2: case 3:
      ROS_INFO("You are bad");
      break;
      case 4: case 5: case 6:
      ROS_INFO("You need to work on it");
      break;
      case 7: case 8: case 9:
      ROS_INFO("You came close");
      break;
    }
    ros::shutdown();
  }


}


  //Compare the word from Publisher, with the word selected from question function
void compare (){


  //If the words are similar, then the value of .compare is 0 (The following 6 lines have been correct with an if-else statement)
    if(word.compare(chosenWord) != 0){
      ROS_INFO("Wrong");
      ROS_INFO("The word was: ");
      ROS_INFO_STREAM(chosenWord);
      counterWrong++;
    }
    else{
      ROS_INFO("Correct");
      ROS_INFO("The word was: ");
      counterCorrect++;
    }
    ROS_INFO_STREAM ("Number of correct answers: " << counterCorrect);
    ROS_INFO_STREAM ("Number of wrong answers: " << counterWrong);
    win_lose();
    question();
}

public:
  //Exam constructor
  Exam()
  {
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
