#ifndef __BOARD__
#define __BOARD__

#include <array>
#include "block.hpp"

class Board {
private: 
    std::array<std::array<Block, 4>, 4> board_;

public: 
    Board();
    
    std::array<Block, 4>& operator[](int i);
    const std::array<Block, 4>& operator[](int i) const;
};

#endif // __BOARD__