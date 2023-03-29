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

bool Format::all(std::string &str, check_bit check) {
    bool out = true;
    if (check & GENDER) out = out && Format::gender(str);
    if (check & NOSPACE) out = out && Format::nospace(str);
    if (check & NOLOWER) out = out && Format::nolower(str);
    return out;
}

void Format::strict_input(std::istream &is, std::ostream &os, const char *prompt, std::string &str, check_bit check) {
    os << prompt;
    is >> str;
    if (!all(str, check)) {
        os << "Invalid input. Input again. " << std::endl;
        strict_input(is, os, prompt, str, check);
    }
}

void Format::range_input(std::istream &is, std::ostream &os, const char *prompt, int &i, int min, int max) {
    os << prompt;
    is >> i;
    if (i < min || i > max) {
        os << "Invalid input. Input again. " << std::endl;
        range_input(is, os, prompt, i, min, max);
    }
}
