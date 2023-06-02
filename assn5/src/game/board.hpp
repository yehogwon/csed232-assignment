#ifndef __BOARD__
#define __BOARD__

#include <array>
#include <ostream>
#include "block.hpp"

const int SIZE = 4;

class Board {
private: 
    std::array<std::array<Block, SIZE>, SIZE> board_;

public: 
    Board();
    Board(const Board& board);
    
    std::array<Block, SIZE>& operator[](int i);
    const std::array<Block, SIZE>& operator[](int i) const;
};

#endif // __BOARD__