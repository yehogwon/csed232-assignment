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

bool Format::all(std::string &str, check_bit check) {
    bool out = true;
    if (check & GENDER) out = out && Format::gender(str);
    if (check & NOSPACE) out = out && Format::nospace(str);
    if (check & NOLOWER) out = out && Format::nolower(str);
    if (check & NOEMPTY) out = out && Format::noempty(str);
    if (check & NUMBER) out = out && Format::number(str);
    return out;
}

void Format::strict_input(std::istream &is, std::ostream &os, const char *prompt, std::string &str, check_bit check) {
    os << prompt;
    std::getline(is, str);
    if (!all(str, check)) {
        os << "Invalid input. Input again. " << std::endl;
        strict_input(is, os, prompt, str, check);
    }
}

void Format::range_input(std::istream &is, std::ostream &os, const char *prompt, int &i, int min, int max) {
    std::string _str;
    strict_input(is, os, prompt, _str, Format::NUMBER | Format::NOEMPTY | Format::NOSPACE);
    i = std::stoi(_str);
    if (i < min || i > max) {
        os << "Invalid input. Input again. " << std::endl;
        range_input(is, os, prompt, i, min, max);
    }
}

std::ostream& operator+(std::ostream &os, double d) {
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
