#ifndef __GAME__
#define __GAME__

#include <iostream>
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

enum Key { UP, DOWN, LEFT, RIGHT };

const int GOAL = 1024;
const int MAX_RESTORE = 3;

class Game {
    using pos = std::pair<int, int>;

    template <int row_start_, int row_end_, int column_start_, int column_end_, bool transpose_>
    struct Direction {
        static int row_start() {
            return row_start_;
        }

        static int row_end() {
            return row_end_;
        }

        static void row_next(int &i_) {
            if (row_start_ <= row_end_) i_++;
            else i_--;
        }
        
        static bool row_comp(int a, int b) {
            return row_start_ <= row_end_ ? a <= b : a >= b;
        }

        static bool row_out_of_range(int x) {
            return x < std::min(row_start_, row_end_) || x > std::max(row_start_, row_end_);
        }

        static int column_start() {
            return column_start_;
        }

        static int column_end() {
            return column_end_;
        }

        static void column_next(int &j_) {
            if (column_start_ <= column_end_) j_++;
            else j_--;
        }
        
        static bool column_comp(int a, int b) {
            return column_start_ <= column_end_ ? a <= b : a >= b;
        }

        static bool column_out_of_range(int x) {
            return x < std::min(column_start_, column_end_) || x > std::max(column_start_, column_end_);
        }

        static pos get(int row_, int column_) {
            return transpose_ ? std::make_pair(column_, row_) : std::make_pair(row_, column_);
        }

        static int expand(int x) {
            if (x == std::min(row_start_, row_end_) || x == std::min(column_start_, column_end_)) return x - 1;
            else return x + 1;
        }
    };

    using Left = Direction<0, SIZE - 1, 0, SIZE - 1, false>;
    using Right = Direction<0, SIZE - 1, SIZE - 1, 0, false>;
    using Up = Direction<0, SIZE - 1, 0, SIZE - 1, true>;
    using Down = Direction<0, SIZE - 1, SIZE - 1, 0, true>;
private: 
    Board *prev_board_;
    Board *board_;

    int score_;
    int restore_count_;

    bool create_block(int n = 1, bool only_two = false);

    // TODO: Use template / functor to simplify these four functions below
    template <typename T_>
    bool pull();

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

template <typename T_>
bool Game::pull() {
    bool is_shifted = false;
    for (int i = T_::row_start(); T_::row_comp(i, T_::row_end()); T_::row_next(i)) {
        int zero_index = -1;
        for (int j = T_::column_start(); T_::column_comp(j, T_::column_end()); T_::column_next(j)) {
            if (zero_index < 0 && (*board_)[T_::get(i, j).first][T_::get(i, j).second] == 0)
                zero_index = j;
            if (zero_index >= 0 && (*board_)[T_::get(i, j).first][T_::get(i, j).second] != 0) {
                is_shifted = true;
                for (int k = zero_index; T_::column_comp(k, j); T_::column_next(k)) {
                    if (T_::column_out_of_range(k + j - zero_index)) break;
                    (*board_)[T_::get(i, k).first][T_::get(i, k).second] = (*board_)[T_::get(i, k + j - zero_index).first][T_::get(i, k + j - zero_index).second];
                    (*board_)[T_::get(i, k + j - zero_index).first][T_::get(i, k + j - zero_index).second] = 0;
                }
                j = zero_index;
                zero_index = -1;
            }
        }
    }
    return is_shifted;
}

#endif // __GAME__