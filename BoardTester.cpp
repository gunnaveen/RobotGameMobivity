#include "Board.h"
#include <iostream>

using namespace std;

int main(){

  Board board(8);

  board.createNodes();
  board.buildGraph();

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
  */



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

}
