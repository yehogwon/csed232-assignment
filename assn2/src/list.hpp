#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include "student.hpp"

struct Node {
    Student data;
    Node *next;
};

class List {
private: 
    // TODO: Declare some necessary private member variables

public: 
    Node *head; // the first node is a dummy node

    List();
    ~List();
    
    void sort();
};

// TODO: Get them into the class
void save_node(List &list, Node *node);
void delete_node(List &list, Node *node);
void swap_node(Node *node1, Node *node2);

bool operator<(const Student &s, const List &list); // Check if the student exists in the list

#endif