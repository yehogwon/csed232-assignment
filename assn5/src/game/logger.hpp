#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "status.hpp"

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