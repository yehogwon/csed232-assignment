#ifndef __IO_HPP__
#define __IO_HPP__

#include <iostream>
#include <string>

class Format { // public comes first following ios convention
public:
    typedef unsigned int check_bit;

    static const check_bit GENDER = 0x1;
    static const check_bit NOSPACE = 0x2;
    static const check_bit NOLOWER = 0x4;

    static void strict_input(std::istream &is, std::ostream &os, const char *prompt, std::string &str, check_bit check);
    static void range_input(std::istream &is, std::ostream &os, const char *prompt, int &i, int min, int max); // inclusive

private: 
    static bool gender(std::string &str);
    static bool nospace(std::string &str);
    static bool nolower(std::string &str);
    static bool all(std::string &str, check_bit check);
};

void clear_buffer(std::istream &is);

#endif