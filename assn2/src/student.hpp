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

#define MIN_AGE 18
#define MAX_AGE 30

class Student {
private: 
    // student information
    std::string dept, gender, name;
    int age;

public: 
    /**
     * @brief Get student information from cin
     */
    Student();
    Student(std::istream &is, std::ostream &os);

    std::string get_dept() const;
    std::string get_gender() const;
    int get_age() const;

    friend bool comp_dept(const Student &s1, const Student &s2);
    friend bool comp_gender(const Student &s1, const Student &s2);

    friend bool operator==(const Student &s1, const Student &s2);
    friend bool operator>(const Student &s1, const Student &s2);
    friend std::ostream& operator<<(std::ostream &os, const Student &s);
};

bool comp_dept(const Student &s1, const Student &s2);
bool comp_gender(const Student &s1, const Student &s2);

bool operator==(const Student &s1, const Student &s2);
bool operator>(const Student &s1, const Student &s2);
bool operator<(const Student &s1, const Student &s2);
std::ostream& operator<<(std::ostream &os, const Student &s);

#endif