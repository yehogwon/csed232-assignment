#ifndef __BLOCK__
#define __BLOCK__

#include <string>

class Block {
private: 
    int value_;
public: 
    bool merged;
    
    Block(); // constructor without argument
    Block(const Block &block); // copy constructor
    
    int& value(); // get the value of the block
    int value() const; // get the value of the block (const)
    std::string color() const; // get the color of the block (according to the value)

    Block& operator*=(int x); // multiply the value of the block by x
    Block& operator=(int value__); // assign value__ to the value of the block
    Block& operator=(const Block& _block); // assign the value of the block to the value of _block (and the merged flag)
    bool operator==(const Block& _block) const; // compare the value of the block with the value of _block
    operator int() const; // cast the block to int (get the value of the block)
};

#endif // __BLOCK__