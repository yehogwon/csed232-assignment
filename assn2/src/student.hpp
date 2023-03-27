#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__

#include <string>

class Student {
private: 
    std::string dept, name, gender;
    int age;

public: 
    void input_info();

    friend bool comp_dept(const Student &s1, const Student &s2);
    friend bool comp_gender(const Student &s1, const Student &s2);

    friend bool operator==(const Student &s1, const Student &s2);
    friend bool operator>(const Student &s1, const Student &s2);
    friend std::ostream& operator<<(std::ostream &os, const Student &s);
};

bool comp_dept(const Student &s1, const Student &s2);
bool comp_gender(const Student &s1, const Student &s2);

struct CompDept;
struct CompGender;

bool operator==(const Student &s1, const Student &s2);
bool operator>(const Student &s1, const Student &s2);
bool operator<(const Student &s1, const Student &s2);
std::ostream& operator<<(std::ostream &os, const Student &s);

#endif