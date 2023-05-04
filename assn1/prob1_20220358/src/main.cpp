/*
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/10
 * ASSN1, Prob #1
 */

#include <iostream>

/**
 * @brief print the number `n` in the base of `base`
 * @param n: integer number to be converted
 * @param base: base of the conversion
 * @return none
*/
void convert(int n, int base) {
    if (n == 0) return; // exit condition (the conversion has ended)
    convert(n / base, base); // call the function recursively

    int rest = n % base; // current digit
    if (rest < 10)
        std::cout << rest; // print the digit as it is
    else
        std::cout << (char) ('A' + rest - 10); // print the digit as a character
}

int main() {
    int num, base; // num: integer number to be converted, base: base (진법) of the conversion
    std::cin >> num >> base; // get the two numbers from the user
    
    if (num == 0)
        std::cout << 0; // if the number is 0, print 0 (not empty)
    else
        convert(num, base); // call convert() to convert the 
    std::cout << std::endl;

    return 0; // Successfully terminated
}
