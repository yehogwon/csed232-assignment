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
    // struct for 2d iteration (row starting / ending index, column starting / ending index, whether it is transposed)
    template <int row_start_, int row_end_, int column_start_, int column_end_, bool transpose_>
    struct Direction {
        static int row_start() {
            return row_start_;
        }

        static int row_end() {
            return row_end_;
        }

        static void row_next(int &i_) { // move the cursor (index) to the next
            i_ += row_next();
        }

        static int row_next() { // +1 if the index is increasing (start <= end), -1 if the index is decreasing (otherwise)
            return row_start_ <= row_end_ ? 1 : -1;
        }

        static bool row_comp(int a, int b) {
            return row_start_ <= row_end_ ? a <= b : a >= b;
        }

        static bool row_out_of_range(int x) {
            return x < std::min(row_start_, row_end_) || x > std::max(row_start_, row_end_);
        }

        // above are used to convert like this: 
        // for (int i = row_start_; i <= row_end_; i++) -> for (int i = row_start_; row_comp(i, row_end_); row_next(i))
        // for (int i = row_start_; i >= row_end_; i--) -> for (int i = row_start_; row_comp(i, row_end_); row_next(i))
        // both of them are converted equivalently. 

        static int column_start() {
            return column_start_;
        }

        static int column_end() {
            return column_end_;
        }

        static void column_next(int &j_) { // move the cursor (index) to the next
            j_ += column_next();
        }

        static int column_next() { // +1 if the index is increasing (start <= end), -1 if the index is decreasing (otherwise)
            return column_start_ <= column_end_ ? 1 : -1;
        }
        
        static bool column_comp(int a, int b) {
            return column_start_ <= column_end_ ? a <= b : a >= b;
        }

        static bool column_out_of_range(int x) {
            return x < std::min(column_start_, column_end_) || x > std::max(column_start_, column_end_);
        }

        // above are used to convert like this: 
        // for (int i = column_start_; i <= column_end_; i++) -> for (int i = column_start_; column_comp(i, column_end_); column_next(i))
        // for (int i = column_start_; i >= column_end_; i--) -> for (int i = column_start_; column_comp(i, column_end_); column_next(i))
        // both of them are converted equivalently. 

        // if the cursor moves up <-> down, the row and column are transposed. in the case, it works exactly
        // the same as left <-> right, but transpose_ = true. 
        static pos get(int row_, int column_) {
            return transpose_ ? pos(column_, row_) : pos(row_, column_);
        }

        // expand the range outwards i.e., 
        // if x is the left-end of the range, expand(x) = x - 1
        // if x is the right-end of the range, expand(x) = x + 1
        static int expand(int x) {
            if (x == std::min(row_start_, row_end_) || x == std::min(column_start_, column_end_)) return x - 1;
            else return x + 1;
        }
    };

    using Left = Direction<0, SIZE - 1, 0, SIZE - 1, false>; // row: 0 -> SIZE - 1, column: 0 -> SIZE - 1
    using Right = Direction<0, SIZE - 1, SIZE - 1, 0, false>; // row: 0 -> SIZE - 1, column: SIZE - 1 -> 0
    using Up = Direction<0, SIZE - 1, 0, SIZE - 1, true>; // row: 0 -> SIZE - 1, column: 0 -> SIZE - 1 (transposed)
    using Down = Direction<0, SIZE - 1, SIZE - 1, 0, true>; // row: 0 -> SIZE - 1, column: SIZE - 1 -> 0 (transposed)
private: 
    Board *prev_board_; // previous board
    Board *board_; // current board

    int score_; // current score
    int restore_count_; // number of restore left

    // function for creating a block. returns the vector of the position of the created blocks and their values.
    std::vector<std::pair<pos, int>> create_block(int n = 1, bool only_two = false);

    template <typename T_>
    bool pull();

    template <typename T_>
    bool merge();

    template <typename T_>
    bool move_();

    void clear_merged(); // clear merged state of all blocks in the current board
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

template <typename T_>
bool Game::pull() {
    bool is_shifted = false; // if any block is shifted
    for (int i = T_::row_start(); T_::row_comp(i, T_::row_end()); T_::row_next(i)) { // for each row (column, if transposed)
        int zero_index = -1;
        for (int j = T_::column_start(); T_::column_comp(j, T_::column_end()); T_::column_next(j)) { // for each column (row, if transposed)
            if (zero_index < 0 && (*board_)[T_::get(i, j).first][T_::get(i, j).second] == 0) // if zero found
                zero_index = j;
            if (zero_index >= 0 && (*board_)[T_::get(i, j).first][T_::get(i, j).second] != 0) { // if zero already had been found and non-zero found
                is_shifted = true; // start shifting
                for (int k = zero_index; T_::column_comp(k, j); T_::column_next(k)) { // iteration between zero index and current index
                    if (T_::column_out_of_range(k + j - zero_index)) break; // the end (out of range is about to occur)
                    (*board_)[T_::get(i, k).first][T_::get(i, k).second] = (*board_)[T_::get(i, k + j - zero_index).first][T_::get(i, k + j - zero_index).second]; // shift
                    (*board_)[T_::get(i, k + j - zero_index).first][T_::get(i, k + j - zero_index).second] = 0; // set empty block (shifted) to zero
                }
                j = zero_index; // start from zero index
                zero_index = -1; // reset zero index
            }
        }
    }
    return is_shifted;
}

template <typename T_>
bool Game::merge() {
    bool is_merged = false; // if any block is merged
    std::vector<std::pair<pos, int>> merged_blocks; // vector of the position of the merged blocks and their values
    for (int i = T_::row_start(); T_::row_comp(i, T_::row_end()); T_::row_next(i)) { // for each row (column, if transposed)
        for (int j = T_::column_start(); T_::column_comp(j, T_::column_end()); T_::column_next(j)) { // for each column (row, if transposed)
            pos cur = T_::get(i, j), next = T_::get(i, j + T_::column_next()); // current position, next position (coordinates)
            if ((*board_)[cur.first][cur.second] == (*board_)[next.first][next.second] && !(*board_)[cur.first][cur.second].merged && !(*board_)[next.first][next.second].merged) { // if the numbers are equal and both blocks had not been merged in this stage
                (*board_)[cur.first][cur.second] *= 2; // merge
                (*board_)[cur.first][cur.second].merged = true; // mark this block as being merged
                (*board_)[next.first][next.second] = 0; // set the other block to zero (the block is removed after being merged)
                is_merged = true; // set merged flag
                score_ += (*board_)[cur.first][cur.second]; // update score
                merged_blocks.push_back(std::make_pair(pos(cur.first + 1, cur.second + 1), (*board_)[cur.first][cur.second])); // record the merged block
            }
        }
    }
    Logger::merge(merged_blocks); // log merged blocks (the positions and their values; they should be printed in sorted order)
    return is_merged;
}

template <typename T_>
bool Game::move_() {
    bool updated = false; // check if board is updated (either pulled or merged, or both)
    // pull, merge, and pull again
    updated = pull<T_>() || updated; // pull first (remove zeros)
    updated = merge<T_>() || updated; // merge
    updated = pull<T_>() || updated; // remove zeros generated by merging
    return updated; // return true if board is updated
}

#endif // __GAME__