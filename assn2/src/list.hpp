#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include "student.hpp"

class Node {
public: 
    Student data;
    Node *next;
};

class List {
private: 
    int count, dept_cnt
    string dept[9];
    Node *head;

public: 
    void sort(std::string metric);
};

#endif