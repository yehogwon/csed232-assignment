#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include "student.hpp"

typedef bool (*Comp)(const Student &s1, const Student &s2);

struct Node {
    Student data;
    Node *next;
};

struct Pivot {
    int max, min;
    double avg;
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
    void sort(Comp comp);
};

void swap_node(Node *node1, Node *node2);

bool operator<(const Student &s, const List &list); // Check if the student exists in the list

#endif