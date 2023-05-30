#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "status.hpp"

#define START_COUT(BUFFER) \
    std::stringstream BUFFER; \
    std::streambuf *__sbuf__ = std::cout.rdbuf(); \
    std::cout.rdbuf(BUFFER.rdbuf());

#define STOP_COUT \
    std::cout.rdbuf(__sbuf__);

std::ostream& operator<<(std::ostream &os, const key &k);
std::ostream& operator<<(std::ostream &os, const pos &p);

class Logger {
public: 
    void static initial(const pos &p1, const pos &p2);
    void static generate(const pos &p, int n);
    void static move(key key);
    void static merge(std::vector<std::pair<pos, int>> &blocks);
    void static restore(int n);
    void static score(int n);
};

#endif // __LOGGER__