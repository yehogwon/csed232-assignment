#include "io.hpp"
#include "test.h"
#include <tuple>
#include <sstream>

bool strict_test() {
    std::pair<const char*, Format::check_bit> proper_cases[] {
        std::make_pair("anything", Format::NOTHING), 
        std::make_pair("M", Format::GENDER), 
        std::make_pair("F", Format::GENDER), 
        std::make_pair("testmsg", Format::NOSPACE),
        std::make_pair("CAP ITAL", Format::NOLOWER),
        std::make_pair("something in", Format::NOEMPTY), 
        std::make_pair("299938", Format::NUMBER),
        std::make_pair("k", Format::ONECHAR),
        std::make_pair("9", Format::ONECHAR),
        std::make_pair("aL phA Bets", Format::ALPHABET), 
        std::make_pair("CAPITAL", Format::NOSPACE | Format::NOLOWER), 
        std::make_pair("28749", Format::NOSPACE | Format::NUMBER), 
        std::make_pair("aLphABets", Format::NOSPACE | Format::ALPHABET),
        std::make_pair("AL LC API TA L", Format::NOLOWER | Format::NOEMPTY), 
        std::make_pair("k", Format::ONECHAR | Format::ALPHABET), 
        std::make_pair("P", Format::ONECHAR | Format::ALPHABET), 
        std::make_pair("PEWPEW", Format::NOSPACE | Format::NOLOWER | Format::ALPHABET)
    };

    bool check = true;
    
    std::string val;
    for (const auto &test_case : proper_cases) {
        if (!check) break;
        std::istringstream iss(test_case.first);
        std::ostringstream oss;
        try {
            Format::strict_input(iss, oss, "prompt", val, test_case.second);
        } catch (InterruptedInputException &e) {
            check = false;
            continue;
        }
        check = check && 
                val == test_case.first && 
                oss.str() == "prompt";
    }
    if (!check) return check;

    std::pair<const char*, Format::check_bit> improper_cases[] { 
        std::make_pair("m", Format::GENDER), 
        std::make_pair("f", Format::GENDER), 
        std::make_pair("white space", Format::NOSPACE),
        std::make_pair("lOWer", Format::NOLOWER),
        std::make_pair("", Format::NOEMPTY), 
        std::make_pair("98aa7", Format::NUMBER),
        std::make_pair("four", Format::ONECHAR),
        std::make_pair("d!i!g!it", Format::ALPHABET), 
        std::make_pair("lowers with space", Format::NOSPACE | Format::NOLOWER), 
        std::make_pair("UPPER BUT SPACE", Format::NOSPACE | Format::NOLOWER), 
        std::make_pair("alphanospace", Format::NOSPACE | Format::NUMBER), 
        std::make_pair("9999 888", Format::NOSPACE | Format::NUMBER), 
        std::make_pair("digit!!nowspace", Format::NOSPACE | Format::ALPHABET),
        std::make_pair("alphabets but space", Format::NOSPACE | Format::ALPHABET),
        std::make_pair("", Format::NOLOWER | Format::NOEMPTY), 
        std::make_pair("lowerHERE", Format::NOLOWER | Format::NOEMPTY), 
        std::make_pair("twoalpha", Format::ONECHAR | Format::ALPHABET), 
        std::make_pair("9", Format::ONECHAR | Format::ALPHABET), 
        std::make_pair("SAT BUT SPACE", Format::NOSPACE | Format::NOLOWER | Format::ALPHABET), 
        std::make_pair("99988", Format::NOSPACE | Format::NOLOWER | Format::ALPHABET), 
        std::make_pair("lowersHERE", Format::NOSPACE | Format::NOLOWER | Format::ALPHABET)
    };

    std::ostringstream _os;
    for (const auto &test_case: improper_cases) {
        if (!check) break;
        std::istringstream iss(std::string(test_case.first) + "\nn\n");
        try {
            Format::strict_input(iss, _os, "", val, test_case.second);
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
        std::make_pair("alks alsjkdf\nn\n", Format::NOSPACE), 
        std::make_pair("JWEjk slkdj\nn\n", Format::NOLOWER),
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
        unittest("Format::strict_input", strict_test), 
        unittest("Format::range_input", range_test),
        unittest("Format::input_again", again_test)
    };
    return test(argv[1], tests);
}
