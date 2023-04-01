#ifndef __IO_HPP__
#define __IO_HPP__

#include <iostream>
#include <iomanip> // FIRE: Implement without using iomanip
#include <string>
#include <cmath>

#define DOUBLE_PRECISION 1
#define DOUBLE_TOLERANCE 1e-6

class Format { // public comes first following ios convention
public:
    typedef unsigned int check_bit;

    static const check_bit GENDER = 0x1;
    static const check_bit NOSPACE = 0x2;
    static const check_bit NOLOWER = 0x4;
    static const check_bit NOEMPTY = 0x8;
    static const check_bit NUMBER = 0x10;

    static void strict_input(std::istream &is, std::ostream &os, const char *prompt, std::string &str, check_bit check);
    static void range_input(std::istream &is, std::ostream &os, const char *prompt, int &i, int min, int max); // inclusive

private: 
    static bool gender(std::string &str);
    static bool nospace(std::string &str);
    static bool nolower(std::string &str);
    static bool noempty(std::string &str);
    static bool number(std::string &str);
    static bool all(std::string &str, check_bit check);
};

std::ostream& operator+(std::ostream &os, double d);

#endif