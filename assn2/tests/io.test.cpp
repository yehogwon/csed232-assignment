#include "io.hpp"
#include "test.h"
#include <tuple>
#include <sstream>

bool strict_test() {
    std::pair<const char*, Format::check_bit> proper_cases[] { 
        std::make_pair("", Format::NOTHING), 
        std::make_pair("", Format::GENDER), 
        std::make_pair("", Format::NOSPACE),
        std::make_pair("", Format::NOLOWER),
        std::make_pair("", Format::NOEMPTY), 
        std::make_pair("", Format::NUMBER),
        std::make_pair("", Format::ONECHAR),
        std::make_pair("", Format::ALPHABET), 
        std::make_pair("", Format::NOSPACE | Format::NOLOWER), 
        std::make_pair("", Format::NOSPACE | Format::NUMBER), 
        std::make_pair("", Format::NOSPACE | Format::ALPHABET),
        std::make_pair("", Format::NOLOWER | Format::NOEMPTY), 
        std::make_pair("", Format::ONECHAR | Format::ALPHABET), 
        std::make_pair("", Format::NOSPACE | Format::NOLOWER | Format::ALPHABET)
    };

    bool check = true;
    
    std::string val;
    for (const auto &test_case : proper_cases) {
        if (!check) break;
        std::istringstream iss(test_case.first);
        std::ostringstream oss;
        Format::strict_input(iss, oss, "prompt", val, test_case.second);
        check = check && 
                val == test_case.first && 
                oss.str() == "prompt";
        
    }
    if (!check) return check;

    std::pair<const char*, Format::check_bit> improper_cases[] { 
        std::make_pair("", Format::NOTHING), 
        std::make_pair("", Format::GENDER), 
        std::make_pair("", Format::NOSPACE),
        std::make_pair("", Format::NOLOWER),
        std::make_pair("", Format::NOEMPTY), 
        std::make_pair("", Format::NUMBER),
        std::make_pair("", Format::ONECHAR),
        std::make_pair("", Format::ALPHABET), 
        std::make_pair("", Format::NOSPACE | Format::NOLOWER), 
        std::make_pair("", Format::NOSPACE | Format::NUMBER), 
        std::make_pair("", Format::NOSPACE | Format::ALPHABET),
        std::make_pair("", Format::NOLOWER | Format::NOEMPTY), 
        std::make_pair("", Format::ONECHAR | Format::ALPHABET), 
        std::make_pair("", Format::NOSPACE | Format::NOLOWER | Format::ALPHABET)
    };

    std::ostringstream _os;
    for (const auto &test_case: improper_cases) {
        if (!check) break;
        std::istringstream iss(test_case.first);
        try {
            Format::strict_input(iss, _os, "prompt", val, test_case.second);
        } catch (InterruptedInputException &e) {
            continue;
        }
        check = false;
    }
    
    return check;
}

bool range_test() {
    std::tuple<int, const char*, int, int> proper_cases[] { 
        std::make_tuple(0, "input: ", 0, 3), 
        std::make_tuple(1, "input: ", 0, 3), 
        std::make_tuple(2, "input: ", 0, 3),
        std::make_tuple(3, "input: ", 0, 3),
        std::make_tuple(0, "value?: ", -5, 3), 
        std::make_tuple(1, "value?: ", -5, 3),
        std::make_tuple(2, "value?: ", -5, 3),
        std::make_tuple(3, "value?: ", -5, 3)
    };

    int val;
    bool check = true;
    std::ostringstream _os;
    for (const auto &test_case : proper_cases) {
        if (!check) break;
        std::istringstream iss(std::to_string(std::get<0>(test_case)));
        Format::range_input(iss, _os, std::get<1>(test_case), val, std::get<2>(test_case), std::get<3>(test_case));
        check = check && 
                val == std::get<0>(test_case) &&
                val >= std::get<2>(test_case) &&
                val <= std::get<3>(test_case);
    }
    if (!check) return check;

    std::tuple<int, const char*, int, int> improper_cases[] { 
        std::make_tuple(-5, "input: ", 0, 3), 
        std::make_tuple(7, "input: ", 0, 3), 
        std::make_tuple(-10, "value?: ", -5, 3),
        std::make_tuple(-2, "value?: ", -5, 3),
        std::make_tuple(38, "value?: ", -5, 3)
    };

    for (const auto &test_case: improper_cases) {
        if (!check) break;
        std::istringstream iss(std::to_string(std::get<0>(test_case)) + "\nn\n");
        try {
            Format::range_input(iss, _os, std::get<1>(test_case), val, std::get<2>(test_case), std::get<3>(test_case));
        } catch (InterruptedInputException &e) {
            continue;
        }
        check = false;
    }
    
    return check;
}

bool again_test() {
    std::pair<std::string, Format::check_bit> test_cases[] {
        // FIXME: These do not work properly; Format::~ | 0 works well. Why?
        // std::make_pair("alks alsjkdf\nn\n", Format::NOSPACE), 
        // std::make_pair("JWEjk slkdj\nn\n", Format::NOLOWER),
        std::make_pair("2993\nn\n", Format::NUMBER | Format::ONECHAR)
    };

    std::string val;
    std::ostringstream _os;
    for (const auto &test_case : test_cases) {
        std::istringstream iss(test_case.first);
        try {
            Format::strict_input(iss, _os, "", val, test_case.second);
        } catch (InterruptedInputException &e) {
            continue;
        }
        return false;
    }
    
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("Format::strict_input", strict_test), 
        std::make_pair("Format::range_input", range_test),
        std::make_pair("Format::input_again", again_test)
    };
    return test(argv[1], tests);
}
