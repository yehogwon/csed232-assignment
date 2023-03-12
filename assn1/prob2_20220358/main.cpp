/*
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/12
 * ASSN1, Prob #2
 */

#include <iostream>
#include <cstring> // for strcmp()
#include <cmath> // for sqrtf()

// Note that sqrtf() gets a float type argument and 
// returns a float type value. 

int main() {
    char op[10]; // operator
    float a, b; // two numbers to be operated

    std::cin >> op; // get the operator from the user

    // Specify the output format; 
    // always show the decimal point at the third digit
    std::cout << std::fixed;
    std::cout.precision(3);
    std::cout.setf(std::ios_base::showpoint);

    // Deal with each operator. 
    // In each case, it gets two or one operand(s) from the user
    // and prints the result. For addition, subtraction, multiplication,
    // division, and square, it gets two operands. For square root, it gets
    // one operand. 
    if (!std::strcmp(op, "+")) { // Do addition
        std::cin >> a >> b;
        std::cout << a + b << std::endl;
    } else if (!std::strcmp(op, "-")) { // Do subtraction
        std::cin >> a >> b;
        std::cout << a - b << std::endl;
    } else if (!std::strcmp(op, "*")) { // Do multiplication
        std::cin >> a >> b;
        std::cout << a * b << std::endl;
    } else if (!std::strcmp(op, "/")) { // Do division
        std::cin >> a >> b;
        std::cout << a / b << std::endl;
    } else if (!std::strcmp(op, "sqrt")) { // Do square root
        std::cin >> a;
        std::cout << sqrtf(a) << std::endl;
    } else if (!std::strcmp(op, "square")) { // square
        std::cin >> a;
        std::cout << a * a << std::endl;
    } else { // When the operator is not one of the above
        std::cout << "Invalid operator" << std::endl; // Print the error message
        return -1; // return the error code (-1)
    }

    return 0; // Successfully terminated
}
