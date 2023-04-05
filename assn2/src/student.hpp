/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: student.hpp
 */

#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__

#include <string>
#include "io.hpp"

#define MIN_AGE 18 // minimum age
#define MAX_AGE 30 // maximum age

class Student {
private: 
    // student information
    std::string dept, gender, name;
    int age;

public: 
    /**
     * @brief default constructor (set std::string variables to "" (empty string) and int variable to 0)
     */
    Student();

    /**
     * @brief constructor to get student information from the user
     * @param is input stream to get student information
     * @param os output stream to show the user what to input (prompt)
     */
    Student(std::istream &is, std::ostream &os);

    /**
     * @brief get department (getter; data hiding)
     * @return dept (const std::string&)
     */
    const std::string& get_dept() const;

    /**
     * @brief get gender (getter; data hiding)
     * @return gender (const std::string&)
     */
    const std::string& get_gender() const;

    /**
     * @brief get age (getter; data hiding)
     * @return age
     */
    int get_age() const;

    // Functions below are friend functions because they need to access private members of Student class (dept, gender, name, age)
    friend bool comp_dept(const Student &s1, const Student &s2);
    friend bool comp_gender(const Student &s1, const Student &s2);

    friend bool operator==(const Student &s1, const Student &s2);
    friend bool operator>(const Student &s1, const Student &s2);
    friend std::ostream& operator<<(std::ostream &os, const Student &s);
};


/**
 * @brief compare two Student objects by dept
 * @param s1 operand 1
 * @param s2 operand 2
 * @return true if s1.dept >= s2.dept, false otherwise
 */
bool comp_dept(const Student &s1, const Student &s2);

/**
 * @brief compare two Student objects by gender
 * @param s1 operand 1
 * @param s2 operand 2
 * @return true if s1.gender >= s2.gender, false otherwise
 */
bool comp_gender(const Student &s1, const Student &s2);

/**
 * @brief compare two Student objects (overloading operator==)
 * @param s1 operand 1
 * @param s2 operand 2
 * @return true if all members of s1 and s2 are equal, false otherwise
 */
bool operator==(const Student &s1, const Student &s2);

/**
 * @brief compare two Student objects (overloading operator>)
 * @param s1 operand 1
 * @param s2 operand 2
 * @return true if s1 > s2 (the order of comparison: dept, gender, name, age)
 */
bool operator>(const Student &s1, const Student &s2);

/**
 * @brief compare two Student objects (overloading operator<)
 * @param s1 operand 1
 * @param s2 operand 2
 * @return true if s1 < s2 (the order of comparison: dept, gender, name, age)
 */
bool operator<(const Student &s1, const Student &s2);

std::ostream& operator<<(std::ostream &os, const Student &s); // print Student object (overloading operator<<)

#endif