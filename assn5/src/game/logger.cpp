#include "logger.hpp"

std::ostream& operator<<(std::ostream &os, const key &k) {
    switch (k) {
        case UP: os << "UP"; break;
        case DOWN: os << "DOWN"; break;
        case LEFT: os << "LEFT"; break;
        case RIGHT: os << "RIGHT"; break;
        default: os << ""; break;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const pos &p) {
    os << p.first << " " << p.second;
    return os;
}

void Logger::initial(const pos &p1, const pos &p2) {
    std::cout << "INITIAL " << p1 << " " << p2 << std::endl;
}

void Logger::generate(const pos &p, int n) {
    std::cout << "GENERATE " << p << " " << n << std::endl;
}

void Logger::move(key key) {
    std::cout << key << std::endl;
}

void Logger::merge(std::vector<std::pair<pos, int>> &blocks) {
    std::sort(blocks.begin(), blocks.end(), [](const std::pair<pos, int> &p1, const std::pair<pos, int> &p2) {
        return p1.first.first < p2.first.first || p1.first.second < p2.first.second;
    });
    for (auto block_ : blocks)
        std::cout << "MERGE " << block_.first << " " << block_.second << std::endl;
}

void Logger::restore(int n) {
    std::cout << "RESTORE " << n << std::endl;
}

void Logger::score(int n) {
    std::cout << "SCORE " << n << std::endl;
}
