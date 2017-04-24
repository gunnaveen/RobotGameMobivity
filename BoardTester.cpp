#include "Board.h"
#include <iostream>

using namespace std;

int main(){

  cout << endl <<"Welcome to the Robot Game!" << endl << endl;

  cout << "└[ ◕ 〜 ◕ ]┘" << endl << endl;

  cout << "Would you like to play?(Y/N): ";
  string reply = "";
  cin >> reply;
  cout << endl << endl;

  while(reply != "N")
  {
    if(reply == "Y")
    {
      cout << "What size board would you like play on?"<< endl;
      cout << "(Ex: enter 4 for a 4*4 board): " ;
      int size = 0;
      cin >> size;
      cout << endl << endl;

      Board board(size);
      board.createNodes();
      board.buildGraph();


      cout << "Version 1: User provides a starting point/direction" << endl;
      cout << "            and instructions for the robot. The game" << endl;
      cout << "            will find the finishing point and direction." << endl << endl;

      cout << "Version 2: User provides a starting point/direction, and" << endl;
      cout << "           a finishing point/direction, and maximum number" << endl;
      cout << "           of moves availble. The game will find all" <<endl;
      cout << "           possible sequences of moves under the limit" <<endl;
      cout << "           that will end in the finishing point/direction."  << endl << endl;

      cout << "Which version would you like to play?(Enter 1 or 2): ";

      int version = 0;
      cin >> version;

      cout << endl << endl;

      if(version == 1)
      {
        board.playVersion1();
        cout << endl << endl;
      }
      else if(version == 2)
      {
        board.playVersion2();
        cout << endl << endl;
      }
      else
      {
        cout << "INVALID INPUT...exiting gameplay." << endl << endl;
      }

      cout << "Would you like to play again?(Y/N): ";
      cin >> reply;
      cout << endl << endl;
    }
    else
    {
      cout << "INVALID INPUT" << endl << endl;
      cout << "Would you like to play?(Y/N): ";
      cin >> reply;
      cout << endl << endl;
    }
  }

  cout << "THANK YOU FOR PLAYING!!!   └[ ◕ 〜 ◕ ]┘" << endl;







  /*
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      Node* test = (board.nodes.find(to_string(i) + to_string(j) + "N"))->second;

      if(test->forward!=NULL)
        test->forward->printNode();
      else
        cout << "Edge properly reached" << endl;

      if(test->left!=NULL)
        test->left->printNode();
      else
        cout << "Edge properly reached" << endl;

      if(test->right!=NULL)
        test->right->printNode();
      else
        cout << "Edge properly reached" << endl;
    }

  }



  Node* test = (board.nodes.find("11N"))->second;

  test->forward->printNode();
  test->left->printNode();
  test->right->printNode();

  if(test->forward->forward == NULL)
    cout << "Edge properly reached" << endl;




  Node* start = board.getNodePointer(2,3,"N");

  Node* target = board.findTargetNode(start, "MMMLMRRR");
  target->printNode();

  Node * end = board.getNodePointer(3,4,"S");

  queue<string> results = board.findAllPaths(start, end, 4);

  if(results.empty())
    cout << "RESULTS NOT FOUND" << endl;

  while(!results.empty())
  {
    string print = results.front();
    results.pop();
    cout<< print << endl;
  }
  */
}
