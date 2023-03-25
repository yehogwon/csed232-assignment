#include "student.hpp"
#include "node.hpp"

Node::Node(Node *next) : next(next) {}

Node::Node(const Student &data, Node *next)
    : data(data), next(next) {}
