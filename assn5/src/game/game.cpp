#include "game.hpp"

Game::Game() : prev_board_(nullptr), board_(new Board()) {
    std::srand(std::time(nullptr));
}

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
    std::vector<std::pair<int, int>> empty_blocks;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == 0)
                empty_blocks.push_back(std::make_pair(i, j));
    if (empty_blocks.size() == 0) return false;
    int index = std::rand() % empty_blocks.size();
    int value = (std::rand() % 2 + 1) * 2;
    (*board_)[empty_blocks[index].first][empty_blocks[index].second] = value;
    return true;
}

void Game::clear_merged() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            (*board_)[i][j].clear_merged();
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
    return is_moved;
}

bool Game::right() {
    // TODO: to be implemented
    return true;
}

bool Game::up() {
    // TODO: to be implemented
    return true;
}

bool Game::down() {
    // TODO: to be implemented
    return true;
}

bool Game::move(Key key) {
    Board *t_prev_ = new Board(*board_);
    bool moved = false;
    switch (key) {
        case UP: moved = up(); break;
        case DOWN: moved = down(); break;
        case LEFT: moved = left(); break;
        case RIGHT: moved = right(); break;
    }
    clear_merged();

    if (moved) {
        if (prev_board_) delete prev_board_;
        prev_board_ = t_prev_;
        create_block();
    } else
        delete t_prev_;

    return moved;
}

std::array<Block, SIZE>& Game::operator[](int i) {
    return (*board_)[i];
}
const std::array<Block, SIZE>& Game::operator[](int i) const {
    return (*board_)[i];
}