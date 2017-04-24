#include "Board.h"
#include <iostream>
using namespace std;


void Node::printNode()
{
	cout << to_string(loc.first) + to_string(loc.second) + dir<< endl;
}



void Board::createNodes()
{
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      nodes.insert(make_pair( (to_string(i) + to_string(j) + "N"), new Node(make_pair(i,j), "N")));
      nodes.insert(make_pair( (to_string(i) + to_string(j) + "E"), new Node(make_pair(i,j), "E")));
      nodes.insert(make_pair( (to_string(i) + to_string(j) + "W"), new Node(make_pair(i,j), "W")));
      nodes.insert(make_pair( (to_string(i) + to_string(j) + "S"), new Node(make_pair(i,j), "S")));
    }
  }
}



void Board::buildGraph()
{
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      //Extracting the n,e,w,s nodes for a particular location in the matrix

			////////////////////////////################################////////////////use function
      Node* north = (nodes.find(to_string(i) + to_string(j) + "N"))->second;
      Node* east = (nodes.find(to_string(i) + to_string(j) + "E"))->second;
      Node* west = (nodes.find(to_string(i) + to_string(j) + "W"))->second;
      Node* south = (nodes.find(to_string(i) + to_string(j) + "S"))->second;

      // Setting the left and right pointeds for each node
      north->left = west;
      north->right = east;
      east->left = north;
      east->right = south;
      west->left = south;
      west->right = north;
      south->left = east;
      south->right = west;

      // Setting the forward pointer for each node
      if(j != 0)
      {
				///////////#####################################/////////////////////////////////Change and use the function
        south->forward = ((nodes.find(to_string(i) + to_string(j-1) + "S")))->second;
      }
			else
			{   north->forward = NULL;   }

      if(j != size-1)
      {
        north->forward = ((nodes.find(to_string(i) + to_string(j+1) + "N")))->second;
      }
			else
			{   south->forward = NULL;   }

			if(i != 0)
      {
        west->forward = ((nodes.find(to_string(i-1) + to_string(j) + "W")))->second;
      }
			else
			{   west->forward = NULL;   }

			if(i != size-1)
      {
        east->forward = ((nodes.find(to_string(i+1) + to_string(j) + "E")))->second;
      }
			else
			{   east->forward = NULL;   }

		}
  }
}


Node* Board::findTargetNode(Node* start, string path)
{
	Node* curr = start;
	string move = "";

	while(path.length() != 0)
	{
		move = path.at(0);
		path = path.substr(1);

		if (move == "M")
		{
			if (curr->forward == NULL)
			{		cerr << "INVALID MOVE. BOARD BOUNDARY REACHED." << endl;   }
			else
			{   curr = curr->forward;			}
		}
 		else if (move == "L")
		{
			if (curr->left == NULL)
			{		cerr << "INVALID MOVE. BOARD BOUNDARY REACHED." << endl;   }
			else
			{   curr = curr->left;			}
		}
		else if (move == "R")
		{
			if (curr->right == NULL)
			{		cerr << "INVALID MOVE. BOARD BOUNDARY REACHED." << endl;   }
			else
			{   curr = curr->right;			}
		}
		else
		{
			cerr << "INVALID MOVE. INVALID SYMBOL ENTERED.";
		}

	}
	return curr;
}

Node* Board::getNodePointer(int x, int y, string dir)
{
	Node* node = (nodes.find(to_string(x) + to_string(y) + dir))->second;
  return node;
}

queue<string> Board::findAllPaths(Node* start, Node* end, int maxMoves)
{
	queue<pair<Node *, string>>  bfs;
	queue<string> results;

	Node* currNode = start;

	pair<Node*, string> currPair = make_pair(currNode, "");

	bfs.push(currPair);

	/* BreadthFirstSearch algorithm */
	while (1)
  {
  	currPair = bfs.front();
    bfs.pop();

		currNode = currPair.first;

		if(currNode == end)
		{
			if( currPair.second.length() <= maxMoves )
			{
				results.push(currPair.second);
			}
			else
			{
				return results;
			}
		}
		if (currNode->forward != NULL)
		{
			bfs.push(make_pair(currNode->forward, currPair.second + "M"));
		}
		if (currNode->left != NULL)
		{
			bfs.push(make_pair(currNode->left, currPair.second + "L"));
		}
		if (currNode->right != NULL)
		{
			bfs.push(make_pair(currNode->right, currPair.second + "R"));
		}
	}
}

//Node::~Node()

Board::~Board()
{
	auto iter = nodes.begin();

	while(iter != nodes.end())
	{
		delete iter->second;
		iter++;
	}
}
