#ifndef __IO_HPP__
#define __IO_HPP__

#include <iostream>
#include <string>
#include <cctype>

typedef bool (*CheckInt)(int);
typedef bool (*CheckStr)(const std::string);

template <int min, int max>
bool range(int i) { // inclusive
    return i >= min && i <= max;
}

bool no_space(const std::string &str);
bool no_lower(const std::string &str);

void input_int(std::istream &is, std::ostream &os, const char *prompt, int &i, CheckInt check);

void input_str(std::istream &is, std::ostream &os, const char *prompt, std::string &str, CheckStr check);

// void input_without_whitespace(const std::istream &is, const std::ostream &os, const T &prompt, std::string &str);

// void input_only_upper(const std::istream &is, const std::ostream &os, const T &prompt, std::string &str);

#endif