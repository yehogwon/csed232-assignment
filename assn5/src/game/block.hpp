#ifndef __BLOCK__
#define __BLOCK__

#include <string>

class Block {
private: 
    int value_;
public: 
    bool merged;
    
    Block();
    Block(const Block &block);
    
    int value() const;
    std::string color() const;

    Block& operator*=(int x);
    Block& operator=(int value__);
    Block& operator=(const Block& _block);
    bool operator==(const Block& _block) const;
    operator int() const;
};

#endif // __BLOCK__