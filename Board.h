#ifndef BOARD_H
#define BOARD_H

#include "Node.h"
#include <string>
#include <utility>
#include <unordered_map>
#include <queue>


class Board
{
	public:
		Board(int sz)
		{
			size = sz;
		}

		Node* matrix;
		std::unordered_map<std::string, Node* > nodes;
		int size;

		void createNodes();

		void buildGraph();

		Node* getNodePointer(int x, int y, std::string dir);

		std::queue<std::string> findAllPaths(Node* start, Node* end, int maxMoves);

		Node* findTargetNode(Node* start, std::string path);

		~Board();

};

#endif
