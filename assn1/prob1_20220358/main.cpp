#include <iostream>

void convert(int n, int base) {
    if (n == 0) return;
    convert(n / base, base);

    int rest = n % base;
    if (rest < 10)
        std::cout << rest;
    else
        std::cout << (char) ('A' + rest - 10);
}

int main() {
    int num, base;
    std::cin >> num >> base;
    
    convert(num, base);
    std::cout << std::endl;

    return 0;
}
