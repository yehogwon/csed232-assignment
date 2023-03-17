#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__

#include <string>

class Student {
private: 
    std::string dept, name, gender;
    int age;
public: 

    void input_info();
};

#endif