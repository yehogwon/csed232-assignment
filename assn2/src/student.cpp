#include <iostream>
#include "student.hpp"

void Student::input_info() {
    std::cout << "Dept: "; std::cin >> dept;
    std::cout << "Gender: "; std::cin >> gender;
    std::cout << "Name: "; std::cin >> name;
    std::cout << "Age: "; std::cin >> age;
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

std::ostream& operator<<(std::ostream &os, const Student &s) {
    os << "{" << s.dept << ", " << s.gender << ", " << s.name << ", " << s.age << "}";
    return os;
}
