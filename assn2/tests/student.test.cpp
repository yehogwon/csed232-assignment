#include "student.hpp"
#include <sstream>

bool input_test() {
    std::istringstream iss("CSE\nM\nKim\n23\n");
    std::ostringstream oss;
    Student s(iss, oss);
    bool check1 = s.get_dept() == "CSE" && s.get_gender() == "M" && s.get_age() == 23;
    return check1;
}

bool output_test() {
    return true;
}

bool equal_test() {
    return true;
}

bool comp_test() {
    return true;
}

int main() {
    return !(input_test() && output_test() && equal_test() && comp_test());
}