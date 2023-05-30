#include "logger.hpp"

std::ostream& operator<<(std::ostream &os, const key &k) {
    switch (k) {
        case UP: os << "UP";
        case DOWN: os << "DOWN";
        case LEFT: os << "LEFT";
        case RIGHT: os << "RIGHT";
        default: os << "";
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const pos &p) {
    os << p.first << " " << p.second;
    return os;
}

void Logger::initial(const pos &p1, const pos &p2) {
    std::cout << "INITIAL" << p1 << " " << p2 << std::endl;
}

void Logger::generate(const pos &p, int n) {
    std::cout << "GENERATE" << p << " " << n << std::endl;
}

void Logger::move(key key) {
    std::cout << key << std::endl;
}

void Logger::merge(const pos &p, int n) {
    std::cout << "MERGE" << p << std::endl;
}

void Logger::restore(int n) {
    std::cout << "RESTORE " << n << std::endl;
}

void Logger::score(int n) {
    std::cout << "SCORE " << n << std::endl;
}
