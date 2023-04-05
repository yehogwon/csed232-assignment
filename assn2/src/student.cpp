/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: student.cpp
 */

#include <iostream>
#include "student.hpp"
#include "exception.hpp"

Student::Student() : dept(""), gender(""), name(""), age(0) { }

Student::Student(std::istream &is, std::ostream &os) {
    // TODO: Put that I have checked the empty-input
    Format::strict_input(is, os, "Dept: ", dept, Format::NOSPACE | Format::NOLOWER | Format::NOEMPTY);
    Format::strict_input(is, os, "Gender: ", gender, Format::NOSPACE | Format::GENDER | Format::NOEMPTY);
    Format::strict_input(is, os, "Name: ", name, Format::NOSPACE | Format::NOEMPTY);
    Format::range_input(is, os, "Age: ", age, MIN_AGE, MAX_AGE);
}

std::string Student::get_dept() const {
    return dept;
}

std::string Student::get_gender() const {
    return gender;
}

int Student::get_age() const {
    return age;
}

bool comp_dept(const Student &s1, const Student &s2) {
    return s1.dept >= s2.dept;
}

bool comp_gender(const Student &s1, const Student &s2) {
    return s1.gender >= s2.gender;
}

bool operator==(const Student &s1, const Student &s2) {
    return s1.dept == s2.dept && s1.gender == s2.gender && s1.name == s2.name && s1.age == s2.age;
}

bool operator>(const Student &s1, const Student &s2) {
    if (s1.dept != s2.dept) return s1.dept > s2.dept;
    else if (s1.gender != s2.gender) return s1.gender > s2.gender;
    else if (s1.name != s2.name) return s1.name > s2.name;
    else return s1.age > s2.age;
}

bool operator<(const Student &s1, const Student &s2) {
    return !(s1 > s2) && !(s1 == s2);
}

std::ostream& operator<<(std::ostream &os, const Student &s) {
    os << s.dept << "\t" << s.gender << "\t" << s.name << "\t" << s.age;
    return os;
}
