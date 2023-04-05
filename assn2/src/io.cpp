/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: io.cpp
 */

#include "io.hpp"

bool Format::gender(std::string &str) {
    return str == "M" || str == "F";
}

bool Format::nospace(std::string &str) {
    for (char ch : str)
        if (ch == ' ')
            return false;
    return true;
}

bool Format::nolower(std::string &str) {
    for (char ch : str)
        if (ch >= 'a' && ch <= 'z')
            return false;
    return true;
}

bool Format::noempty(std::string &str) {
    return !str.empty();
}

bool Format::number(std::string &str) {
    for (char ch : str)
        if (ch < '0' || ch > '9')
            return false;
    return true;
}

bool Format::onechar(std::string &str) {
    return str.length() == 1;
}

bool Format::all(std::string &str, check_bit check) {
    bool out = true;
    if (check & GENDER) out = out && Format::gender(str);
    if (check & NOSPACE) out = out && Format::nospace(str);
    if (check & NOLOWER) out = out && Format::nolower(str);
    if (check & NOEMPTY) out = out && Format::noempty(str);
    if (check & NUMBER) out = out && Format::number(str);
    if (check & ONECHAR) out = out && Format::onechar(str);
    return out;
}

bool Format::input_again(std::istream &is, std::ostream &os) {
    std::string _str;
    strict_input(is, os, "Invalid input. Will you input again (y/n) [y]? ", _str, Format::NOEMPTY | Format::NOSPACE | Format::ONECHAR);
    return _str != "n";
}

void Format::strict_input(std::istream &is, std::ostream &os, const char *prompt, std::string &str, check_bit check) {
    os << prompt;
    std::getline(is, str);
    if (!all(str, check)) {
        if (input_again(is, os)) strict_input(is, os, prompt, str, check);
        else throw InterruptedInputException();
    }
}

void Format::range_input(std::istream &is, std::ostream &os, const char *prompt, int &i, int min, int max) {
    std::string _str;
    strict_input(is, os, prompt, _str, Format::NUMBER | Format::NOEMPTY | Format::NOSPACE);
    i = std::stoi(_str);
    if (i < min || i > max) {
        if (input_again(is, os)) return range_input(is, os, prompt, i, min, max);
        else throw InterruptedInputException();
    }
}

std::ostream& operator+(std::ostream &os, double d) {
    // TODO: mention this in the report
    if (std::abs(d - std::round(d)) < DOUBLE_TOLERANCE) {
        os.precision(0);
        os << d;
    } else {
        os << std::fixed;
        os.setf(std::ios_base::showpoint);
        os.precision(DOUBLE_PRECISION);
        os << d;
        os.unsetf(std::ios_base::showpoint);
    }
    return os;
}
