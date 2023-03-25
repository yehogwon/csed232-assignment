#ifndef __NODE_HPP__
#define __NODE_HPP__

class Node {
public: 
    Student data;
    Node *next;

    Node(Node *next = nullptr);
    Node(const Student &data, Node *next = nullptr);
};

#endif