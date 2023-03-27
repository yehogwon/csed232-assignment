#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include "student.hpp"

struct Node {
    Student data;
    Node *next;
};

bool operator==(const Node &n1, const Node &n2);

class List {
private: 
    // TODO: Declare some necessary private member variables for performing pivot table operations

public: 
    Node *head; // the first node is a dummy node

    List();
    ~List();

    void add(Node *node);
    void remove(Node *node);
    
    void sort();
};

void swap_node(Node *node1, Node *node2);

bool operator<(const Student &s, const List &list); // Check if the student exists in the list

#endif