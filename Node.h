#ifndef NODE_H
#define NODE_H

#include <string>
#include <utility>


class Node
{
  private:
    std::string dir;
    std::pair<int, int> loc;
  public:
    Node(std::pair<int, int> location, std::string direction) {
      dir = direction;
      loc = location;
    }

    Node* forward;
    Node* left;
    Node* right;

    void printNode();

};

#endif
