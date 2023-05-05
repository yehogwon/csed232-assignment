#include "student.hpp"
#include <string>
#include <sstream>
#include <tuple>

bool input_test() {
    std::pair<const char*, std::tuple<const char*, const char*, int>> proper_cases[] {
        std::make_pair("CSE\nM\nKim\n23\n", std::make_tuple("CSE", "M", 23)), 
        std::make_pair("BIO\nF\nNana\n29\n", std::make_tuple("BIO", "F", 29))
    };

    bool check = true;
    for (auto test_case : proper_cases) {
        if (!check) break;
        std::istringstream iss(test_case.first);
        std::ostringstream oss;
        Student s(iss, oss);
        check = check && 
                s.get_dept() == std::get<0>(test_case.second) && 
                s.get_gender() == std::get<1>(test_case.second) && 
                s.get_age() == std::get<2>(test_case.second);
    }
    if (!check) return check;
    
    return check;
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