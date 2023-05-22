#ifndef __BLOCK__
#define __BLOCK__

#include <string>

class Block {
private: 
    int value_;
public: 
    Block();
    
    int value() const;
    std::string color() const;

    Block& operator*=(int x);
    void operator=(int value__);
    void operator=(const Block& _block);
    bool operator==(const Block& _block) const;
    operator int() const;
};

#endif // __BLOCK__