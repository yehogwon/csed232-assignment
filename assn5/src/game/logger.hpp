#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include "status.hpp"

std::ostream& operator<<(std::ostream &os, const key &k);
std::ostream& operator<<(std::ostream &os, const pos &p);

class Logger {
public: 
    void static initial(const pos &p1, const pos &p2);
    void static generate(const pos &p, int n);
    void static move(key key);
    void static merge(const pos &p, int n);
    void static restore(int n);
    void static score(int n);
};

#endif // __LOGGER__