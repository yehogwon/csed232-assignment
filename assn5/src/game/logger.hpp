#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "status.hpp"

// #define for catching std::cout
// log is printed to the console so we should catch it
// this #define declares a std::stringstream and redirects std::cout to the stringstream
#define START_COUT(BUFFER) \
    std::stringstream BUFFER; \
    std::streambuf *__sbuf__ = std::cout.rdbuf(); \
    std::cout.rdbuf(BUFFER.rdbuf());

// this #define restores std::cout
// reconnect std::cout to the original buffer
#define STOP_COUT \
    std::cout.rdbuf(__sbuf__);

std::ostream& operator<<(std::ostream &os, const key &k); // print key
std::ostream& operator<<(std::ostream &os, const pos &p); // print position (coordinate)

class Logger {
public: 
    void static initial(const pos &p1, const pos &p2); // print INITIAL
    void static generate(const pos &p, int n); // print GENERATE
    void static move(key key); // print arrow key name
    void static merge(std::vector<std::pair<pos, int>> &blocks); // print MERGE; multiple blocks might have been merged, so we use std::vector (sort it before printing)
    void static restore(int n); // print RESTORE
    void static score(int n); // print SCORE
};

#endif // __LOGGER__