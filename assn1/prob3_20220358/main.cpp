#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <iomanip>

int get_base(std::string s) {
    if (s.find("0b") == 0) return 2;
    else if (s.find("0X") == 0) return 16;
    else if (s[0] == '0') return 8;
    return 10;
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

int to_int(std::string s) {
    int base = get_base(s);
    int num = 0, idx = 0;
    for (auto cit = s.crbegin(); cit != s.crend() && *cit != 'b' && *cit != 'X'; cit++) {
        int cur = is_digit(*cit) ? *cit - '0' : *cit - 'A' + 10;
        num += cur * pow(base, idx++);
    }
    return num;
}

int main() {
    char op;
    std::string a, b;

    std::cin >> op >> a >> b;
    std::cout << std::fixed << std::setprecision(3);

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
