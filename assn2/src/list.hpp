/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/06
 * File Name: list.hpp
 */

#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream> // Only for pivot table functions (print the results)
#include <string>
#include "student.hpp"
#include "node.hpp"
#include "io.hpp"

#define MAX_AGE 30 // maximum age of students
#define MAX_DEPT 9 // maximum number of departments
#define MAX_GENDER 2 // the number of types of gender ("M" / "F")
#define MAX_DEPT_GENDER (MAX_DEPT * MAX_GENDER)
#define MAX_STUDENT 10000 // the maximum number of students in a department

typedef bool (*Comp)(const Student &s1, const Student &s2); // function pointer type (Student, Student) -> bool

enum Operator { AVG = 1, MAX = 2, MIN = 3 }; // enum type for indiciating a pivot table operator

class List {
private: 
    struct Pivot { // struct to store the result of pivot table (accumulate)
        int max, min, cnt, sum;
    };

    struct DeptStatus { // struct to store the status of departments (the name of the department and the number of students in the department)
        std::string dept;
        int cnt;
    };

    Node *head; // head node; used as a dummy node

    DeptStatus dept_status[MAX_DEPT]; // store the departments as an array (the name of each department and the number of students in the department)

    /**
     * @brief return the number of departments in the list
     * @return the total number of departments in the list
     */
    int get_total_dept_cnt() const;

public: 
    /**
     * @brief constructor
     */
    List();
    /**
     * @brief destructor
     */
    ~List();

    /**
     * @brief add a node to the list
     * @param node node to be added
     * @return true if the node is added successfully, false otherwise
     */
    bool add(Node *node);

    /**
     * @brief remove a node from the list
     * @param node node to be removed
     * @return true if the node is removed successfully, false otherwise
     */
    bool remove(Node *node);

    /**
     * @brief print the list
     * @return none
     */
    void print();

    /**
     * @brief sort the list following the instruction using selection sort algorithm (dept > gender > name > age; ascending order)
     * @return none
     */
    void sort();

    /**
     * @brief sort the list following the given comparison function using selection sort algorithm
     * @param comp comparison function (function pointer that gets two Student objects and returns the order in bool type)
     * @return none
     */
    void sort(Comp comp);

    /**
     * @brief conduct pivot table with dept as a pivot variable with the given operator and print the result
     * @param op operator to conduct pivot table with
     * @return none
     */
    void pivot_dept(Operator op);

    /**
     * @brief conduct pivot table with gender as a pivot variable with the given operator and print the result
     * @param op operator to conduct pivot table with
     * @return none
     */
    void pivot_gender(Operator op);

    /**
     * @brief conduct pivot table with dept and gender as a pivot variable with the given operator and print the result
     * @param op operator to conduct pivot table with
     * @return none
     */
    void pivot_dept_gender(Operator op);

    friend bool operator<(const Student &s, const List &list);
};

/**
 * @brief convert the given operator to string (the name of the operator)
 * @param op operator to be converted
 * @return name (Average, Max, Min) of the operator
 */
std::string to_string(Operator op);

/**
 * @brief find the maximum value of two arguments
 * @tparam T type of the two arguments and return value
 * @param a first argument
 * @param b second argument
 * @return the maximum value of the two arguments
 */
template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

/**
 * @brief find the minimum value of two arguments
 * @tparam T type of the two arguments and return value
 * @param a first argument
 * @param b second argument
 * @return the minimum value of the two arguments
 */
template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

/**
 * @brief check if the Student object (s) is in the list (list) (operator overloading)
 * @param s Student object to be checked
 * @param list list to be checked from
 * @return true if s is in the list, false otherwise
 */
bool operator<(const Student &s, const List &list); // Check if the student exists in the list

#endif