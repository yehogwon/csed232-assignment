#ifndef __BLOCK__
#define __BLOCK__

#include <string>

class Block {
private: 
    int value_;
public: 
    Block();
    
    int get_value() const;
    std::string get_color() const;
    operator int() const;
};

#endif // __BLOCK__