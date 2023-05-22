#ifndef __GAME__
#define __GAME__

#include <array>
#include "block.hpp"
#include "board.hpp"

class Game {
private: 
    Board *prev_board_;
    Board *board_;

    bool create_block();
public: 
    Game();
    ~Game();

    const Board& prev() const;
    const Board& cur() const;

    bool left();
    bool right();
    bool up();
    bool down();

    bool is_game_over();

    std::array<Block, SIZE>& operator[](int i);
    const std::array<Block, SIZE>& operator[](int i) const;    
};

#endif // __GAME__