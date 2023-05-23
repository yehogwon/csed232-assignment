#ifndef __GAME__
#define __GAME__

#include <array>
#include <vector>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <queue>
#include "block.hpp"
#include "board.hpp"
#include "status.hpp"

enum Key { UP, DOWN, LEFT, RIGHT };

const int GOAL = 2048;
const int MAX_RESTORE = 3;

class Game {
private: 
    // TODO: Should it be pointer?
    Board *prev_board_;
    Board *board_;

    int score_;
    int restore_count_;

    bool create_block(bool only_two = false);

    // TODO: Use template / functor to simplify these four functions below
    bool pull_left();
    bool pull_right();
    bool pull_up();
    bool pull_down();

    bool merge_left();
    bool merge_right();
    bool merge_up();
    bool merge_down();

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
    int score() const;

    bool move(Key key);
    bool is_game_win() const;
    bool is_game_over() const;

    bool restore();
    bool restorable() const;
    int restore_remain() const;

    std::array<Block, SIZE>& operator[](int i);
    const std::array<Block, SIZE>& operator[](int i) const;    
};

#endif // __GAME__