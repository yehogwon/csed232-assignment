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
    // get input from the user under the following conditions:
    // (1) dept should not contain space and should consist only of uppercase. Also, it should not be empty. 
    Format::strict_input(is, os, "Dept: ", dept, Format::ALPHABET | Format::NOSPACE | Format::NOLOWER | Format::NOEMPTY);
    // (2) gender should either "M", "F". So, it should not contain whitespace and be empty.
    Format::strict_input(is, os, "Gender: ", gender, Format::ALPHABET | Format::NOSPACE | Format::GENDER | Format::NOEMPTY);
    // (3) name should not contain whitespace and be empty. 
    Format::strict_input(is, os, "Name: ", name, Format::ALPHABET | Format::NOSPACE | Format::NOEMPTY);
    // (4) age should be a integer and within the range of MIN_AGE and MAX_AGE (inclusive)
    Format::range_input(is, os, "Age: ", age, MIN_AGE, MAX_AGE);
}

const std::string& Student::get_dept() const {
    return dept;
}

const std::string& Student::get_gender() const {
    return gender;
}

int Student::get_age() const {
    return age;
}

bool comp_dept(const Student &s1, const Student &s2) {
    return s1.dept >= s2.dept; // compare dept of s1 and s2
}

bool comp_gender(const Student &s1, const Student &s2) {
    return s1.gender >= s2.gender; // compare gender of s1 and s2
}

bool operator==(const Student &s1, const Student &s2) {
    // compare every member variables of s1 and s2
    return s1.dept == s2.dept && s1.gender == s2.gender && s1.name == s2.name && s1.age == s2.age;
}

bool operator>(const Student &s1, const Student &s2) {
    // the order of comparison is dept > gender > name > age
    if (s1.dept != s2.dept) return s1.dept > s2.dept;
    else if (s1.gender != s2.gender) return s1.gender > s2.gender;
    else if (s1.name != s2.name) return s1.name > s2.name;
    else return s1.age > s2.age;
}

bool operator<(const Student &s1, const Student &s2) {
    return !(s1 > s2) && !(s1 == s2); // trichotomy property
}

std::ostream& operator<<(std::ostream &os, const Student &s) {
    // print dept, gender, name, age separated by tab
    os << s.dept << "\t" << s.gender << "\t" << s.name << "\t" << s.age;
    return os;
}
