#include "io.hpp"

bool no_space(const std::string &str) {
    for (char ch : str)
        if (isspace(ch))
            return false;
    return true;
}

bool no_lower(const std::string &str) {
    for (char ch : str)
        if (islower(ch))
            return false;
    return true;
}

void input_int(std::istream &is, std::ostream &os, const char *prompt, int &i, CheckInt check) {
    os << prompt;
    is >> i;
    if (!check(i)) {
        os << "Invalid input. Input again. " << std::endl;
        input_int(is, os, prompt, i, check);
    }
}

void input_str(std::istream &is, std::ostream &os, const char *prompt, std::string &str, CheckStr check) {
    os << prompt;
    is >> str;
    if (!check(str)) {
        os << "Invalid input. Input again. " << std::endl;
        input_str(is, os, prompt, str, check);
    }
}
