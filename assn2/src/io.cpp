/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: io.cpp
 */

#include "io.hpp"

bool Format::gender(std::string &str) {
    return str == "M" || str == "F"; // check if str is "M" or "F"
}

bool Format::nospace(std::string &str) {
    for (char ch : str)
        if (ch == ' ') // str contains at least one space
            return false; // if so, return false
    return true; // otherwise, return true
}

bool Format::nolower(std::string &str) {
    for (char ch : str)
        if (ch >= 'a' && ch <= 'z') // str contains at least one lowercase letter
            return false; // if so, return false
    return true; // otherwise, return true
}

bool Format::noempty(std::string &str) {
    return !str.empty(); // return if str is NOT empty
}

bool Format::number(std::string &str) {
    for (char ch : str)
        if (ch < '0' || ch > '9') // str contains at least one non-digit character
            return false; // if so, return false
    return true; // otherwise, return true
}

bool Format::onechar(std::string &str) {
    return str.length() == 1; // return if str has only one character
}

bool Format::alphabet(std::string &str) {
    for (char ch : str)
        if ((ch < 'A' || ch > 'Z') && (ch < 'a' || ch > 'z') && ch != ' ') // str contains at least one non-alphabet character
            return false; // if so, return false
    return true; // otherwise, return true
}

bool Format::all(std::string &str, check_bit check) {
    bool out = true; // initialize out to true (default value is true)
    // One of them is false, out will be false
    // Check when out is true; Once it turns false, it will not be checked anymore
    if (out && (check & GENDER)) out = out && Format::gender(str);
    if (out && (check & NOSPACE)) out = out && Format::nospace(str);
    if (out && (check & NOLOWER)) out = out && Format::nolower(str);
    if (out && (check & NOEMPTY)) out = out && Format::noempty(str);
    if (out && (check & NUMBER)) out = out && Format::number(str);
    if (out && (check & ONECHAR)) out = out && Format::onechar(str);
    if (out && (check & ALPHABET)) out = out && Format::alphabet(str);
    return out;
}

bool Format::input_again(std::istream &is, std::ostream &os) {
    std::string _str; // temporary string to store user's choice
    strict_input(is, os, "Invalid input. Will you input again (y/n) [y]? ", _str, Format::NOTHING);
    return _str != "n"; // if user's choice is not "n", return true (default choice is "y")
}

void Format::strict_input(std::istream &is, std::ostream &os, const char *prompt, std::string &str, check_bit check) {
    os << prompt; // print prompt
    std::getline(is, str); // get user's input all along the line
    if (!all(str, check)) { // if user's input is invalid (does not satisfy the condition)
        if (input_again(is, os)) strict_input(is, os, prompt, str, check); // ask user if he/she wants to input again; if so, call this function again (recursion)
        else throw InterruptedInputException(); // otherwise, throw InterruptedInputException to notice that user has interrupted the input process
    }
}

void Format::range_input(std::istream &is, std::ostream &os, const char *prompt, int &i, int min, int max) {
    std::string _str; // declare a temporary string to store user's input
    strict_input(is, os, prompt, _str, Format::NUMBER | Format::NOEMPTY | Format::NOSPACE); // get user's input
    // I got a number with getline() as a string, not with in >> i to handle exceptions (the input may NOT be a number)
    i = std::stoi(_str); // convert string to integer
    if (i < min || i > max) { // if user's input is out of range (not within min and max)
        if (input_again(is, os)) return range_input(is, os, prompt, i, min, max); // ask user if he/she wants to input again; if so, call this function again (recursion)
        else throw InterruptedInputException(); // otherwise, throw InterruptedInputException to notice that user has interrupted the input process
    }
}

std::ostream& operator+(std::ostream &os, double d) {
    if (std::abs(d - std::round(d)) < DOUBLE_TOLERANCE) { // if d has no decimal part
        os << (int) std::round(d); // print round(d) as an integer
    } else {
        os << std::fixed; // set fixed-point notation
        os.setf(std::ios_base::showpoint); // set showpoint (print decimal point even if it is 0)
        os.precision(DOUBLE_PRECISION); // set precision to DOUBLE_PRECISION (1; following the instruction)
        os << d; // print d
        os.unsetf(std::ios_base::showpoint); // unset showpoint
    }
    return os;
}
