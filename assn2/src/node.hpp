#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "student.hpp"

struct Node {
    Student data;
    Node *next;
};

bool operator==(const Node &n1, const Node &n2);

#endif