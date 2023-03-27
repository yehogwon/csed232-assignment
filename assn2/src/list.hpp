#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream>
#include <string>
#include "student.hpp"

// #define INT_MAX 10000000 // TODO: Update this line
#define MAX_DEPT 9

typedef bool (*Comp)(const Student &s1, const Student &s2);

struct Node {
    Student data;
    Node *next;
};

struct Pivot {
    int max, min, cnt, sum;
};

bool operator==(const Node &n1, const Node &n2);

// TODO: Mark const methods
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

    void pivot_dept(int op);
    void pivot_gender(int op);
    void pivot_dept_gender(int op);
};

template <typename T>
T max(T a, T b);

template <typename T>
T min(T a, T b);

void swap_node(Node *node1, Node *node2);

bool operator<(const Student &s, const List &list); // Check if the student exists in the list

#endif