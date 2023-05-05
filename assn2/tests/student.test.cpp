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
    std::ostringstream oss;
    for (const auto &test_case : proper_cases) {
        if (!check) break;
        std::istringstream iss(test_case.first);
        Student s(iss, oss);
        check = check && 
                s.get_dept() == std::get<0>(test_case.second) && 
                s.get_gender() == std::get<1>(test_case.second) && 
                s.get_age() == std::get<2>(test_case.second);
    }
    if (!check) return check;

    const char *improper_cases[] {
        "CS E\nn\n", 
        "CssE\nn\n", 
        "BIO\naf\nn\n",
        "BIO\nF\nj23 a\nn\n",
        "BIO\nF\nNana\n14\nn\n"
    };
    for (const auto &test_case: improper_cases) {
        if (!check) break;
        std::istringstream iss(test_case);
        try {
            Student s(iss, std::cout);
        } catch (InterruptedInputException &e) {
            continue;
        }
        check = false;
    }
    
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