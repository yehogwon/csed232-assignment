/*
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/10
 * ASSN1, Prob #1
 */

#include <iostream>

/**
 * @brief print the number `n` in the notation of `notation`
 * @param n: integer number to be converted
 * @param notation: notation of the conversion
 * @return none
*/
void convert(int n, int notation) {
    if (n == 0) return; // exit condition (the conversion has ended)
    convert(n / notation, notation); // call the function recursively

    int rest = n % notation; // current digit
    if (rest < 10)
        std::cout << rest; // print the digit as it is
    else
        std::cout << (char) ('A' + rest - 10); // print the digit as a character
}

int main() {
    int num, notation; // num: integer number to be converted, notation: notation (진법) of the conversion
    std::cin >> num >> notation; // get the two numbers from the user
    
    convert(num, notation); // call convert() to convert the 
    std::cout << std::endl;

    return 0; // Successfully terminated
}
