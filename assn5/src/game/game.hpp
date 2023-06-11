#ifndef __GAME__
#define __GAME__

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <set>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <queue>
#include "block.hpp"
#include "board.hpp"
#include "status.hpp"
#include "logger.hpp"

const int GOAL = 2048; // goal of the game
const int MAX_RESTORE = 3; // maximum number of restore

class Game {
private: 
    Board *prev_board_; // previous board
    Board *board_; // current board

    int score_; // current score
    int restore_count_; // number of restore left

    // function for creating a block. returns the vector of the position of the created blocks and their values.
    std::vector<std::pair<pos, int>> create_block(int n = 1, bool only_two = false);

public: 
    Game();
    ~Game();

    const Board& prev() const; // get the reference of the previous board
    const Board& cur() const; // get the reference of the current board
    int score() const; // get the current score

    bool move(key key); // move the board according to the key. returns if any change is made
    bool is_game_win() const; // check if the game is win
    bool is_game_over() const; // check if the game is over

    bool restore(); // restore the previous board. returns if any change is made
    bool restorable() const; // check if the game is restorable (i.e., previous state exists)
    int restore_remain() const; // get the number of restore left

    std::array<Block, SIZE>& operator[](int i); // indexing; return the ith row of the current board
    const std::array<Block, SIZE>& operator[](int i) const; // indexing; return the ith row of the current board (const version)
};

#endif // __GAME__