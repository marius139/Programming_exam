#include "ros/ros.h"
#include "ros/console.h"

//we're using this type of message to pass a string between nodes
#include "std_msgs/String.h"
#include "iostream"
#include "string"
#include "vector"

//we're using the time to calculate a "random" number
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
  int counterCorrect;
  int counterWrong;
  int counterWord;

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
//Switchcase for 10 answers
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

  //counterWord keeps track of if the word is spelled correctly
  counterWord=0;

  //Here we check if the word is spelled correctly
  //First we check if the user typed in a word of the correct length
  if(word.size()==chosenWord.size()) {
    //if the length  is correct, we use a for loop to compare all the characters in the two words
    for (int i = 0; i<chosenWord.size(); i++) {
      //if the two characters are equal to each other, increase the chosenWord counter
      if (word[i]==chosenWord[i]) {
          counterWord++;

          //if the two characters are NOT equal to each other
        } else {
          //write message to the terminal, and increase the counter for the amount of wrong words
          ROS_INFO("Wrong");
          ROS_INFO("The word was: ");
          ROS_INFO_STREAM(chosenWord);
          counterWrong++;
          //break out of the for loop
          break;
    }
  }

//if the two words are not of equal size
} else {
  //write message to the terminal, and increase the counter for the amount of wrong words
  ROS_INFO("Wrong");
  ROS_INFO("The words arent the same length");
  counterWrong++;
}
  //if the for loop has successfully run through all the letters of the word, it is spelled correctly
  if(counterWord==chosenWord.size()) {
    ROS_INFO("Correct");
    //increase the counter for amount of correct words
    counterCorrect++;
  }
    //write a message to terminal, and call functions win_lose and question
    ROS_INFO_STREAM ("Number of correct answers: " << counterCorrect);
    ROS_INFO_STREAM ("Number of wrong answers: " << counterWrong);
    win_lose();
    question();
}

public:
  //Exam constructor
  Exam()
  {
    //set the counters to 0
    counterCorrect=0;
    counterWrong=0;
  //  wordList.push_back("toast");
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
