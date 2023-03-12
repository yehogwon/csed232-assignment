#include <iostream>
#include <cstring>
#include <cmath>

int main() {
    char op[10];
    float a, b;

    std::cin >> op;

    std::cout << std::fixed;
    std::cout.precision(3);
    std::cout.setf(std::ios_base::showpoint);
    if (!std::strcmp(op, "+")) {
        std::cin >> a >> b;
        std::cout << a + b << std::endl;
    } else if (!std::strcmp(op, "-")) {
        std::cin >> a >> b;
        std::cout << a - b << std::endl;
    } else if (!std::strcmp(op, "*")) {
        std::cin >> a >> b;
        std::cout << a * b << std::endl;
    } else if (!std::strcmp(op, "/")) {
        std::cin >> a >> b;
        std::cout << a / b << std::endl;
    } else if (!std::strcmp(op, "sqrt")) {
        std::cin >> a;
        std::cout << sqrtf(a) << std::endl;
    } else if (!std::strcmp(op, "square")) {
        std::cin >> a;
        std::cout << a * a << std::endl;
    } else {
        std::cout << "Invalid operator" << std::endl;
        return 0;
    }

    return 0;
}
