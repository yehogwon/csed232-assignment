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

bool operator==(const Node &n1, const Node &n2);

enum Operator { AVG = 1, MAX = 2, MIN = 3 };

class List {
private: 
    struct Pivot {
        int max, min, cnt, sum;
    };

    std::string to_string(Operator op) const;

public: 
    Node *head; // the first node is a dummy node

    List();
    ~List();

    void add(Node *node);
    void remove(Node *node);
    
    void sort();
    void sort(Comp comp);

    void pivot_dept(Operator op);
    void pivot_gender(Operator op);
    void pivot_dept_gender(Operator op);
};

template <typename T>
T max(T a, T b);

template <typename T>
T min(T a, T b);

void swap_node(Node *node1, Node *node2);

bool operator<(const Student &s, const List &list); // Check if the student exists in the list

#endif