#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>

/* Example IO
 * + 1.35 2.47       ->      3.820
 * * 3.986 2.515     ->      10.025
 * / 24.999 3.900    ->      6.410
 * - -101.35 2.47    ->      -103.820
 * square 4          ->      16
 * sqrt 4            ->      2
 */

int main() {
    char op[10];
    float a, b;

    std::cin >> op;
    std::cout << std::fixed << std::setprecision(3);
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
