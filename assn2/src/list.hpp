#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include "student.hpp"

class Node {
public: 
    Student data;
    Node *next;

    Node(const Student &data, Node *next = nullptr);
};

class List {
private: 
    int count, dept_cnt;
    std::string dept[9];
    Node *head;

public: 
    void sort(std::string metric);
    Node& operator[](int i);
};

void save_node(List &list, Node *node);
void delete_node(List &list, Node *node);

bool operator<(const Student &s, const List &list);

#endif