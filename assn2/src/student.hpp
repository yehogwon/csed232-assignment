#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__

#include <string>

class Student {
public: 
    std::string dept, name, gender;
    int age;

    void input_info();
};

bool operator==(const Student &s1, const Student &s2);

#endif