#ifndef __GAME__
#define __GAME__

#include <array>
#include <vector>
#include <utility>
#include <ctime>
#include <cstdlib>
#include "block.hpp"
#include "board.hpp"

enum Key { UP, DOWN, LEFT, RIGHT };

class Game {
private: 
    Board *prev_board_;
    Board *board_;

    bool create_block();

    bool left();
    bool right();
    bool up();
    bool down();

    void clear_merged();
public: 
    Game();
    ~Game();

    const Board& prev() const;
    const Board& cur() const;

    bool move(Key key);
    bool is_game_over();

    std::array<Block, SIZE>& operator[](int i);
    const std::array<Block, SIZE>& operator[](int i) const;    
};

#endif // __GAME__