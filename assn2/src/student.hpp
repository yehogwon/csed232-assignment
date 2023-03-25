#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__

#include <string>

class Student {
public: 
    std::string dept, name, gender;
    int age; // 0: Male, 1: Female

    void input_info();
};

bool operator==(const Student &s1, const Student &s2);
std::ostream& operator<<(std::ostream &os, const Student &s);

#endif