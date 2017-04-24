#include "Board.h"
#include <iostream>
using namespace std;


void Node::printNode()
{
	cout << "[" + to_string(loc.first) + "," + to_string(loc.second) + "," + dir + "]"<< endl;
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
      Node* north = getNodePointer(i,j,"N");
      Node* east = getNodePointer(i,j,"E");
      Node* west = getNodePointer(i,j,"W");
      Node* south = getNodePointer(i,j,"S");

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
        south->forward = getNodePointer(i,j-1,"S");
			}
			else
			{   south->forward = NULL;   }

      if(j != size-1)
      {
        north->forward = getNodePointer(i,j+1,"N");
      }
			else
			{   north->forward = NULL;   }

			if(i != 0)
      {
        west->forward = getNodePointer(i-1,j,"W");
      }
			else
			{   west->forward = NULL;   }

			if(i != size-1)
      {
        east->forward = getNodePointer(i+1,j,"E");
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
			{
				cout << "INVALID MOVE, BOARD BOUNDARY REACHED...exiting gameplay." << endl;
				return NULL;
			}
			else
			{   curr = curr->forward;			}
		}
 		else if (move == "L")
		{
			if (curr->left == NULL)
			{
				cout << "INVALID MOVE, BOARD BOUNDARY REACHED...exiting gameplay." << endl;
				return NULL;
			}
			else
			{   curr = curr->left;			}
		}
		else if (move == "R")
		{
			if (curr->right == NULL)
			{
				cout << "INVALID MOVE, BOARD BOUNDARY REACHED...exiting gameplay." << endl;
				return NULL;
			}
			else
			{   curr = curr->right;			}
		}
		else
		{
			cerr << "INVALID SYMBOLS IN PATH...exiting gameplay.";
			return NULL;
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

void Board::playVersion1()
{
	cout << "Version 1" << endl << endl;
	cout << "Enter a x-coordinate for the starting point: ";
	int x = 0;
	cin >> x;
	cout << endl;
	if(x >= size || x < 0)
	{
		cout << "INVALID INPUT for x-coordinate...exiting gameplay." << endl;
		return;
	}

	cout << "Enter a y-coordinate for the starting point: ";
	int y = 0;
	cin >> y;
	cout << endl;
	if(y >= size || y < 0)
	{
		cout << "INVALID INPUT for y-coordinate...exiting gameplay." << endl;
		return;
	}

	cout << "Enter a direction for the starting point(N/E/W/S): ";
	string dir = "";
	cin >> dir;
	cout << endl;
	if(dir != "N" && dir != "E" && dir != "W" && dir != "S")
	{
		cout << "INVALID INPUT for direction...exiting gameplay." << endl;
		return;
	}

	cout << "Enter the moves that the robot will perform." << endl;
	cout << "M for go forward, L to turn left, R to turn right." << endl;
	cout << "Input in the following format -> MRMLRM: ";
	string path = "";
	cin >> path;
	cout << endl;

	Node* start = getNodePointer(x,y,dir);

	Node* target = findTargetNode(start, path);
	if(target == NULL)
		return;
	cout << "The Robot finishes at: ";
	target->printNode();
}

void Board::playVersion2()
{
	cout << "Version 2" << endl << endl;
	cout << "Enter a x-coordinate for the starting point: ";
	int x1 = 0;
	cin >> x1;
	cout << endl;
	if(x1 >= size || x1 < 0)
	{
		cout << "INVALID INPUT for x-coordinate...exiting gameplay." << endl;
		return;
	}

	cout << "Enter a y-coordinate for the starting point: ";
	int y1 = 0;
	cin >> y1;
	cout << endl;
	if(y1 >= size || y1 < 0)
	{
		cout << "INVALID INPUT for y-coordinate...exiting gameplay." << endl;
		return;
	}

	cout << "Enter a direction for the starting point(N/E/W/S): ";
	string dir1 = "";
	cin >> dir1;
	cout << endl;
	if(dir1 != "N" && dir1 != "E" && dir1 != "W" && dir1 != "S")
	{
		cout << "INVALID INPUT for direction...exiting gameplay." << endl;
		return;
	}

	cout << "Enter a x-coordinate for the ending point: ";
	int x2 = 0;
	cin >> x2;
	cout << endl;
	if(x2 >= size || x2 < 0)
	{
		cout << "INVALID INPUT for x-coordinate...exiting gameplay." << endl;
		return;
	}

	cout << "Enter a y-coordinate for the ending point: ";
	int y2 = 0;
	cin >> y2;
	cout << endl;
	if(y2 >= size || y2 < 0)
	{
		cout << "INVALID INPUT for y-coordinate...exiting gameplay." << endl;
		return;
	}

	cout << "Enter a direction for the ending point(N/E/W/S): ";
	string dir2 = "";
	cin >> dir2;
	cout << endl;
	if(dir2 != "N" && dir2 != "E" && dir2 != "W" && dir2 != "S")
	{
		cout << "INVALID INPUT for direction...exiting gameplay." << endl;
		return;
	}

	cout << "Enter the maximum number of moves that the" << endl;
	cout << "robot is allowed to make: ";
	int max = 0;
	cin >> max;
	cout << endl;


	Node* start = getNodePointer(x1,y1,dir1);

  Node* end = getNodePointer(x2,y2,dir2);

  queue<string> results = findAllPaths(start, end, max);

  if(results.empty())
  {
		cout << "RESULTS NOT FOUND" << endl;
		return;
	}

	cout << "These are all the paths found: " << endl;

  while(!results.empty())
  {
    string print = results.front();
    results.pop();
    cout<< print << endl;
  }

}



Board::~Board()
{
	auto iter = nodes.begin();

	while(iter != nodes.end())
	{
		delete iter->second;
		iter++;
	}
}
