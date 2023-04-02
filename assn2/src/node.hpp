#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "student.hpp"

class Node {
public: 
    Student data;
    Node *next;

    Node(Student data, Node *next);
};

bool operator==(const Node &n1, const Node &n2);

void swap_node(Node *node1, Node *node2);

#endif