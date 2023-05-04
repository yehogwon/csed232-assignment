/*
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/13
 * ASSN1, Prob #3
 */

#include <iostream>
#include <string>
#include <cmath> // for pow()
#include <cctype> // for isdigit()

/**
 * @brief Get the base (진법) of input string (focus on the prefix)
 * @param s: string of number to check the base
 * @return: the base of the input string
*/
int get_base(std::string s) {
    if (s.find("0b") == 0) return 2; // If the string starts with "0b" -> binary
    else if (s.find("0X") == 0) return 16; // If the string starts with "0X" -> hexadecimal
    else if (s[0] == '0') return 8; // If the string starts with '0' -> octal
    return 10; // Otherwise, decimal
}

/**
 * @brief convert input string to a integer number
 * @param s: string of number to check the base
 * @return: converted integer value
*/
int to_int(std::string s) {
    int base = get_base(s); // the base of the input string
    int num = 0, idx = 0; // num: the resultant integer value, idx: the index of the digit
    for (int i = s.length() - 1; i >= 0 && s[i] != 'b' && s[i] != 'X'; i--) {
        // Repeat until the index reaches the beginning of the string or the prefix of the base
        int cur = isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10; // current digit; convert if it is a character (hex)
        num += cur * pow(base, idx++); // add the current digit to the result
    }
    return num; // return the result
}

int main() {
    char op; // operator
    std::string a, b; // operands in string

    std::cin >> op >> a >> b; // read the input (operator and two operands)

    // Specify the output format; 
    // always show the decimal point at the third digit
    std::cout << std::fixed;
    std::cout.precision(3);
    std::cout.setf(std::ios_base::showpoint);

    // Conduct the operation and print the result
    switch (op) {
        case '+': // Addition 
            std::cout << to_int(a) + to_int(b) << std::endl;
            break;
        case '-': // Subtraction
            std::cout << to_int(a) - to_int(b) << std::endl;
            break;
        case '*': // Multiplication
            std::cout << to_int(a) * to_int(b) << std::endl;
            break;
        case '/': // Division
            std::cout << (double) to_int(a) / to_int(b) << std::endl;
            // Note that the result should be a double value
            break;
        default: // if the operator is invalid
            std::cout << "Invalid operator" << std::endl;
            return -1; // return -1 to indicate the error
    }

    return 0; // Successfully terminated
}
