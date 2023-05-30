#include "logger.hpp"

std::ostream& operator<<(std::ostream &os, const Key &k) {
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

void static initial(const pos &&p1, const pos &&p2) {
    std::cout << "INITIAL" << p1.first << " " << p1.second << " " << p2.first << " " << p2.second << std::endl;
}

void static generate(const pos &&p, int n) {
    std::cout << "GENERATE" << p.first << " " << p.second << " " << n << std::endl;
}

void static move(Key key) {
    std::cout << key << std::endl;
}

void static merge(const pos &&p, int n) {
    std::cout << "MERGE" << p.first << " " << p.second << " " << n << std::endl;
}

void static restore(int n) {
}

void static score(int n) {
}
