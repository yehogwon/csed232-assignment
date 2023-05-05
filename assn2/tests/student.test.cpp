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
            Student s(iss, oss);
        } catch (InterruptedInputException &e) {
            continue;
        }
        check = false;
    }
    
    return check;
}

bool output_test() {
    std::pair<const char*, const char*> cases[] {
        std::make_pair("CSE\nM\nKim\n23\n", "CSE\tM\tKim\t23"), 
        std::make_pair("BIO\nF\nNana\n29\n", "BIO\tF\tNana\t29")
    };

    bool check = true;
    for (const auto &test_case : cases) {
        if (!check) break;
        std::istringstream iss(test_case.first);
        std::ostringstream oss;
        Student s(iss, std::cout);
        oss << s;
        std::cout << std::endl << oss.str() << std::endl;
        check = check && 
                oss.str() == test_case.second;
    }
    
    return check;
}

bool equal_test() {
    const char *cases[] {
        "CSE\nM\nKim\n23\n",
        "BIO\nF\nNana\n29\n", 
        "MATH\nM\nKim\n20\n", 
        "CSE\nF\nKim\n23\n",
        "MECH\nM\nSam\n23\n"
    };
    
    bool check = true;
    std::ostringstream oss;
    for (int i = 0; i < 5; i++) {
        for (int j = i; j < 5; j++) {
            if (!check) break;
            std::istringstream iss1(cases[i]);
            std::istringstream iss2(cases[j]);
            Student s1(iss1, oss);
            Student s2(iss2, oss);

            if (i == j) {
                check = check && (s1 == s2);
            } else {
                check = check && !(s1 == s2);
            }
        }
    }

    return check;
}

bool comp_test() {
    return true;
}

int main() {
    return !(input_test() && output_test() && equal_test() && comp_test());
}