#include "logger.hpp"

std::ostream& operator<<(std::ostream &os, const key &k) {
    // print the key name
    switch (k) {
        case UP: os << "UP"; break;
        case DOWN: os << "DOWN"; break;
        case LEFT: os << "LEFT"; break;
        case RIGHT: os << "RIGHT"; break;
        default: os << ""; break; // unexpected case
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const pos &p) {
    os << p.first << " " << p.second; // print the position (row, column) separated by a space
    return os;
}

void Logger::initial(const pos &p1, const pos &p2) {
    std::cout << "INITIAL " << p1 << " " << p2 << std::endl; // print the initially generated two blocks
}

void Logger::generate(const pos &p, int n) {
    std::cout << "GENERATE " << p << " " << n << std::endl; // print the position and the value of the generated block
}

void Logger::move(key key) {
    std::cout << key << std::endl; // print the key name
}

void Logger::merge(std::vector<std::pair<pos, int>> &blocks) {
    // sort the blocks by the position (row, column) <- row first, column second
    std::sort(blocks.begin(), blocks.end(), [](const std::pair<pos, int> &p1, const std::pair<pos, int> &p2) {
        if (p1.first.first == p2.first.first) return p1.first.second < p2.first.second;
        else return p1.first.first < p2.first.first;
    });
    for (auto block_ : blocks)
        std::cout << "MERGE " << block_.first << " " << block_.second << std::endl; // print the position and the value of the merged block
}

void Logger::restore(int n) {
    std::cout << "RESTORE " << n << std::endl; // print the number of chances remained
}

void Logger::score(int n) {
    std::cout << "SCORE " << n << std::endl; // print the score
}
