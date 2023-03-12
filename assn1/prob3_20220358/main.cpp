/*
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/00
 * ASSN1, Prob #3
 */

#include <iostream>
#include <string>
#include <cmath> // for pow()
#include <cctype> // for isdigit()

int get_base(std::string s) {
    if (s.find("0b") == 0) return 2;
    else if (s.find("0X") == 0) return 16;
    else if (s[0] == '0') return 8;
    return 10;
}

int to_int(std::string s) {
    int base = get_base(s);
    int num = 0, idx = 0;
    for (int i = s.length() - 1; i >= 0 && s[i] != 'b' && s[i] != 'X'; i--) {
        int cur = isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
        num += cur * pow(base, idx++);
    }
    return num;
}

int main() {
    char op;
    std::string a, b;

    std::cin >> op >> a >> b;

    // Specify the output format; 
    // always show the decimal point at the third digit
    std::cout << std::fixed;
    std::cout.precision(3);
    std::cout.setf(std::ios_base::showpoint);

    switch (op) {
        case '+': 
            std::cout << to_int(a) + to_int(b) << std::endl;
            break;
        case '-':
            std::cout << to_int(a) - to_int(b) << std::endl;
            break;
        case '*':
            std::cout << to_int(a) * to_int(b) << std::endl;
            break;
        case '/':
            std::cout << (double) to_int(a) / to_int(b) << std::endl;
            break;
        default: 
            std::cout << "Invalid operator" << std::endl;
            return -1;
    }

    return 0;
}
