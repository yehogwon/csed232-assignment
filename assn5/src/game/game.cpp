#include "game.hpp"

Game::Game() : prev_board_(nullptr), board_(new Board()) { }

Game::~Game() {
    if (prev_board_)
        delete prev_board_;
    delete board_;
}

bool Game::is_game_over() {
    // TODO: to be implemented
    return false;
}
    
bool Game::create_block() {
    // TODO: to be implemented
    if (prev_board_) delete prev_board_;
    prev_board_ = board_;
    board_ = new Board(*prev_board_);
    return true;
}

const Board& Game::prev() const {
    return *prev_board_;
}

const Board& Game::cur() const {
    return *board_;
}

bool Game::left() {
    bool is_moved = false;
    for (int i = 0; i < SIZE; i++) {
        // for each row
        while (true) {
            // remove spaces
            int zero_index = -1;
            bool is_shifted = false;
            for (int j = 0; j < SIZE; j++) {
                if (zero_index < 0 && (*board_)[i][j] == 0)
                    zero_index = j;
                if (zero_index >= 0 && (*board_)[i][j] != 0) {
                    is_shifted = true;
                    for (int k = zero_index; k < j; k++) {
                        if (k + j - zero_index >= SIZE) break;
                        (*board_)[i][k] = (*board_)[i][k + j - zero_index];
                        (*board_)[i][k + j - zero_index] = 0;
                    }
                }
            }
            if (zero_index == -1 || !is_shifted) break;
            
            // merge
            bool is_merged = false;
            for (int j = 0; j < SIZE - 1; j++) {
                if ((*board_)[i][j] == (*board_)[i][j + 1]) {
                    (*board_)[i][j] *= 2;
                    (*board_)[i][j + 1] = 0;
                    is_merged = true;
                }
            }
            
            is_moved = is_moved || is_merged;
            if (!is_merged) break;
        }
    }
    create_block();
    return is_moved;
}

bool Game::right() {
    // TODO: to be implemented
    create_block();
    return true;
}

bool Game::up() {
    // TODO: to be implemented
    create_block();
    return true;
}

bool Game::down() {
    // TODO: to be implemented
    create_block();
    return true;
}

std::array<Block, SIZE>& Game::operator[](int i) {
    return (*board_)[i];
}
const std::array<Block, SIZE>& Game::operator[](int i) const {
    return (*board_)[i];
}