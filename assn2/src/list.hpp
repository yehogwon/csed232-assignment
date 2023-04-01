#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream> // Only for pivot table functions
#include <iomanip> // FIRE: Check if this is useable
#include <string>
#include "student.hpp"
#include "node.hpp"
#include "io.hpp"

#define MAX_AGE 30
#define MAX_DEPT 9
#define MAX_GENDER 2
#define MAX_DEPT_GENDER MAX_DEPT * MAX_GENDER

typedef bool (*Comp)(const Student &s1, const Student &s2);

enum Operator { AVG = 1, MAX = 2, MIN = 3 };

class List {
private: 
    struct Pivot {
        int max, min, cnt, sum;
    };

    Node *head; // the first node is a dummy node

    std::string to_string(Operator op) const;

public: 
    List();
    ~List();

    void add(Node *node);
    void remove(Node *node);

    void print(std::string sep = "\n") const; // TODO: Is it proper to put the default value here? Not in the source?
    
    void sort();
    void sort(Comp comp);

    // TODO: Optimize the pivot table functions
    void pivot_dept(Operator op);
    void pivot_gender(Operator op);
    void pivot_dept_gender(Operator op);

    friend bool operator<(const Student &s, const List &list);
};

template <typename T>
T max(T a, T b);

template <typename T>
T min(T a, T b);

bool operator<(const Student &s, const List &list); // Check if the student exists in the list

#endif