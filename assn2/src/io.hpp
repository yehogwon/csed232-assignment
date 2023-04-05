/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: io.hpp
 */

#ifndef __IO_HPP__
#define __IO_HPP__

#include <iostream>
#include <string>
#include <cmath>
#include "exception.hpp"

#define DOUBLE_PRECISION 1 // the number of decimal places to print
#define DOUBLE_TOLERANCE 1e-6 // the tolerance of double comparison

class Format { // public comes first following ios convention
public:
    typedef unsigned int check_bit; // bit mask for checking input

    static const check_bit GENDER = 0x1;   // 0000 0001 : string only "M" or "F"
    static const check_bit NOSPACE = 0x2;  // 0000 0010 : string without whitespace
    static const check_bit NOLOWER = 0x4;  // 0000 0100 : string without lowercase (all uppercase)
    static const check_bit NOEMPTY = 0x8;  // 0000 1000 : not empty string
    static const check_bit NUMBER = 0x10;  // 0001 0000 : string only digits
    static const check_bit ONECHAR = 0x20; // 0010 0000 : string only one character

    /**
     * @brief get input from user in string type with some format (gender, nospace, ...)
     * @param is: input stream to get input
     * @param os: output stream to print prompt
     * @param prompt: prompt to print
     * @param str: string to store input
     * @param check: bit mask for checking input (conditions to check)
     * @return none
     * @throw InterruptedInputException
     */
    static void strict_input(std::istream &is, std::ostream &os, const char *prompt, std::string &str, check_bit check);

    /**
     * @brief get numerical input from user in int type with some format (gender, nospace, ...)
     * @param is: input stream to get input
     * @param os: output stream to print prompt
     * @param prompt: prompt to print
     * @param i: int to store input
     * @param min: minimum value of input
     * @param max: maximum value of input
     * @return none
     * @throw InterruptedInputException
     */
    static void range_input(std::istream &is, std::ostream &os, const char *prompt, int &i, int min, int max); // inclusive

private: 
    /**
     * @brief check if a string is a gender
     * @param str: string to check
     * @return true if str is "M" or "F", false otherwise
     */
    static bool gender(std::string &str);

    /**
     * @brief check if a string has no whitespace
     * @param str: string to check
     * @return true if str has no whitespace, false otherwise
     */
    static bool nospace(std::string &str);

    /**
     * @brief check if a string has only uppercase
     * @param str: string to check
     * @return true if str has only uppercase, false otherwise
     */
    static bool nolower(std::string &str);

    /**
     * @brief check if a string is not empty
     * @param str: string to check
     * @return true if str is not empty, false otherwise
     */
    static bool noempty(std::string &str);

    /**
     * @brief check if a string is a number
     * @param str: string to check
     * @return true if str is a number, false otherwise
     */
    static bool number(std::string &str);

    /**
     * @brief check if a string consists of only one character
     * @param str: string to check
     * @return true if str contains only one character, false otherwise
     */
    static bool onechar(std::string &str);

    /**
     * @brief check if a string satisfies all conditions using bit mask
     * @param str: string to check
     * @return true if str satisfies all conditions, false otherwise (one or more conditions are not satisfied)
     */
    static bool all(std::string &str, check_bit check);

    /**
     * @brief check if user want to input again when the previous one did not satisfy the condition
     * @param is: input stream to get input
     * @param os: output stream to print prompt
     * @return true if user want to input again, false otherwise
     */
    static bool input_again(std::istream &is, std::ostream &os);
};

std::ostream& operator+(std::ostream &os, double d); // print double with precision

#endif