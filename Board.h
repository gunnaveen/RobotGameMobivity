#ifndef BOARD_H
#define BOARD_H

#include "Node.h"
#include <string>
#include <utility>
#include <unordered_map>
#include <queue>


class Board
{
	private:
		std::unordered_map<std::string, Node* > nodes;
		int size;

	public:
		Board(int sz)
		{
			size = sz;
		}

		void createNodes();

		void buildGraph();

		Node* getNodePointer(int x, int y, std::string dir);

		std::queue<std::string> findAllPaths(Node* start, Node* end, int maxMoves);

		Node* findTargetNode(Node* start, std::string path);

		void playVersion1();

		void playVersion2();

		~Board();

};

#endif
