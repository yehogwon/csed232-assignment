#ifndef __BOARD__
#define __BOARD__

#include <array>
#include <ostream>
#include "block.hpp"

const int SIZE = 4; // size of the board (the number of cells in a row/column)

class Board {
private: 
    std::array<std::array<Block, SIZE>, SIZE> board_; // std::array to store the blocks (4x4 = 16)

public: 
    Board(); // constructor without arguments (do nothing)
    Board(const Board& board); // copy constructor

    Board& operator=(const Board& board); // copy assignment operator
    
    std::array<Block, SIZE>& operator[](int i); // overload operator[] to access the blocks (ith row)
    const std::array<Block, SIZE>& operator[](int i) const; // overload operator[] to access the blocks (ith row) (const version)
};

#endif // __BOARD__