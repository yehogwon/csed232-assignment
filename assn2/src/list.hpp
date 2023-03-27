#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include "student.hpp"

struct Node {
    Student data;
    Node *next;
};

class List {
public: 
    int count, dept_cnt;
    std::string dept[9];
    Node *head; // the first node is a dummy node

    List();
    ~List();
    
    void sort();
};

void save_node(List &list, Node *node);
void delete_node(List &list, Node *node);
void swap_node(Node *node1, Node *node2);

bool operator<(const Student &s, const List &list); // Check if the student exists in the list

#endif