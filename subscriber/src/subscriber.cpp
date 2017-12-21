#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "iostream"
#include "string"
#include "vector"
#include "time.h"

//
class Exam
{
  ros::NodeHandle nh;
  ros::Subscriber sub;
  std::string word;
  std::vector<std::string> wordList;
  std::string chosenWord;
  int iRand;
  int arrSize;
  int counterCorrect;
  int counterWrong;
  int counterWord;

private:
  //Picks a random word from a vector of words
void question(){
  srand(time(NULL));
  iRand = rand() % wordList.size();
  chosenWord = wordList[iRand];
  ROS_INFO_STREAM(chosenWord);
  wordList.erase(wordList.begin() + iRand);
}

  //Takes word from publisher and compares it to the word from question
void sbCallback (const std_msgs::String::ConstPtr& msg){
  word=msg->data;
  ROS_INFO("You wrote: ");
  ROS_INFO_STREAM(word);
  compare();
}
//Different statements announced dependent on performance
void win_lose(){
  if (counterCorrect+counterWrong == 10) {
    switch (counterWrong) {
      case 0:
      ROS_INFO("FANTASTIC!");
      break;
      case 1: case 2: case 3:
      ROS_INFO("You did good");
      break;
      case 4: case 5: case 6:
      ROS_INFO("You did OK");
      break;
      case 7: case 8: case 9:
      ROS_INFO("You participated");
      case 10:
      ROS_INFO("I feel sorry for you");
      break;
    }
    ros::shutdown();
  }
}

  //Compare the word from Publisher, with the word selected from question function
void compare() {

  counterWord=0;
  if(word.size()==chosenWord.size()) {
    for (int i = 0; i<chosenWord.size(); i++) {
      if (word[i]==chosenWord[i]) {
          counterWord++;
       } 
      else {
          ROS_INFO("Wrong");
          ROS_INFO("The word was: ");
          ROS_INFO_STREAM(chosenWord);
          counterWrong++;
          break;
    }
  }

} else {
  ROS_INFO("Wrong");
  ROS_INFO("The words arent the same length");
  counterWrong++;
}
  if(counterWord==chosenWord.size()) {
    ROS_INFO("Correct");
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
    counterCorrect=0;
    counterWrong=0;
    
    wordList.push_back("toast");
    wordList.push_back("beers");
    wordList.push_back("trees");
    wordList.push_back("bees");
    wordList.push_back("fees");
    wordList.push_back("beautiful");
    wordList.push_back("shawarma");
    wordList.push_back("christmas");
    wordList.push_back("daniel");
    wordList.push_back("jonathan");
    wordList.push_back("kim");
    wordList.push_back("marius");
    wordList.push_back("oskar");
    wordList.push_back("anton");
    wordList.push_back("karl");
    wordList.push_back("matthias");
    wordList.push_back("programming");
    wordList.push_back("turtlebot");
    wordList.push_back("santa");
    wordList.push_back("death");
    wordList.push_back("exam");
    
    question();

  sub = nh.subscribe("game", 10, &Exam::sbCallback,this);
  };
//Exam deconstructor
~Exam(){};
};

int main(int argc, char **argv) {
  ros::init (argc, argv, "subscriber");
  Exam a;
  ros::spin();

  return 0;
}
