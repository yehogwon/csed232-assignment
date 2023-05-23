#include "game.hpp"

Game::Game() : prev_board_(nullptr), board_(new Board()), score_(0), restore_count_(0) {
    std::srand(std::time(nullptr));
    create_block(true); create_block(true);
}

Game::~Game() {
    if (prev_board_)
        delete prev_board_;
    delete board_;
}

bool Game::is_game_win() const {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == GOAL) return true;
    return false;
}

bool Game::is_game_over() const {
    bool can_move = false;
    for (int i = 0; i < SIZE && !can_move; i++)
        for (int j = 0; j < SIZE && !can_move; j++)
            if ((*board_)[i][j] == 0) can_move = true;
    
    for (int i = 0; i < SIZE && !can_move; i++)
        for (int j = 0; j < SIZE - 1 && !can_move; j++)
            if ((*board_)[i][j] == (*board_)[i][j + 1]) can_move = true;
    
    for (int i = 0; i < SIZE - 1 && !can_move; i++)
        for (int j = 0; j < SIZE && !can_move; j++)
            if ((*board_)[i][j] == (*board_)[i + 1][j]) can_move = true;

    return !can_move;
}

bool Game::create_block(bool only_two) {
    std::vector<std::pair<int, int>> empty_blocks;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == 0)
                empty_blocks.push_back(std::make_pair(i, j));
    if (empty_blocks.size() == 0) return false;
    int index = std::rand() % empty_blocks.size();
    int value = std::rand() % 5 == 0 && !only_two ? 4 : 2;
    (*board_)[empty_blocks[index].first][empty_blocks[index].second] = value;
    return true;
}

void Game::clear_merged() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            (*board_)[i][j].merged = false;
}

const Board& Game::prev() const {
    return *prev_board_;
}

const Board& Game::cur() const {
    return *board_;
}

int Game::score() const {
    return score_;
}

bool Game::pull_left() {
    bool is_shifted = false;
    for (int i = 0; i < SIZE; i++) {
        int zero_index = -1;
        for (int j = 0; j < SIZE; j++) {
            if (zero_index < 0 && (*board_)[i][j] == 0)
                zero_index = j;
            if (zero_index >= 0 && (*board_)[i][j] != 0) {
                is_shifted = true;
                for (int k = zero_index; k <= j; k++) {
                    if (k + j - zero_index >= SIZE) break;
                    (*board_)[i][k] = (*board_)[i][k + j - zero_index];
                    (*board_)[i][k + j - zero_index] = 0;
                }
                j = zero_index;
                zero_index = -1;
            }
        }
    }
    return is_shifted;
}

bool Game::pull_right() {
    bool is_shifted = false;
    for (int i = 0; i < SIZE; i++) {
        int zero_index = -1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (zero_index < 0 && (*board_)[i][j] == 0)
                zero_index = j;
            if (zero_index >= 0 && (*board_)[i][j] != 0) {
                is_shifted = true;
                for (int k = zero_index; k >= j; k--) {
                    if (k + j - zero_index < 0) break;
                    (*board_)[i][k] = (*board_)[i][k + j - zero_index];
                    (*board_)[i][k + j - zero_index] = 0;
                }
                j = zero_index;
                zero_index = -1;
            }
        }
    }
    return is_shifted;
}

bool Game::pull_up() {
    bool is_shifted = false;
    for (int i = 0; i < SIZE; i++) {
        int zero_index = -1;
        for (int j = 0; j < SIZE; j++) {
            if (zero_index < 0 && (*board_)[j][i] == 0)
                zero_index = j;
            if (zero_index >= 0 && (*board_)[j][i] != 0) {
                is_shifted = true;
                for (int k = zero_index; k <= j; k++) {
                    if (k + j - zero_index >= SIZE) break;
                    (*board_)[k][i] = (*board_)[k + j - zero_index][i];
                    (*board_)[k + j - zero_index][i] = 0;
                }
                j = zero_index;
                zero_index = -1;
            }
        }
    }
    return is_shifted;
}

bool Game::pull_down() {
    bool is_shifted = false;
    for (int i = 0; i < SIZE; i++) {
        int zero_index = -1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (zero_index < 0 && (*board_)[j][i] == 0)
                zero_index = j;
            if (zero_index >= 0 && (*board_)[j][i] != 0) {
                is_shifted = true;
                for (int k = zero_index; k >= j; k--) {
                    if (k + j - zero_index < 0) break;
                    (*board_)[k][i] = (*board_)[k + j - zero_index][i];
                    (*board_)[k + j - zero_index][i] = 0;
                }
                j = zero_index;
                zero_index = -1;
            }
        }
    }
    return is_shifted;
}

bool Game::merge_left() {
    bool is_merged = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if ((*board_)[i][j] == (*board_)[i][j + 1] && !(*board_)[i][j].merged && !(*board_)[i][j + 1].merged) {
                (*board_)[i][j] *= 2;
                (*board_)[i][j].merged = true;
                (*board_)[i][j + 1] = 0;
                is_merged = true;
                score_ += (*board_)[i][j];
            }
        }
    }
    return is_merged;
}

bool Game::merge_right() {
    bool is_merged = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 1; j > 0; j--) {
            if ((*board_)[i][j] == (*board_)[i][j - 1] && !(*board_)[i][j].merged && !(*board_)[i][j - 1].merged) {
                (*board_)[i][j] *= 2;
                (*board_)[i][j].merged = true;
                (*board_)[i][j - 1] = 0;
                is_merged = true;
                score_ += (*board_)[i][j];
            }
        }
    }
    return is_merged;
}

bool Game::merge_up() {
    bool is_merged = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if ((*board_)[j][i] == (*board_)[j + 1][i] && !(*board_)[j][i].merged && !(*board_)[j + 1][i].merged) {
                (*board_)[j][i] *= 2;
                (*board_)[j][i].merged = true;
                (*board_)[j + 1][i] = 0;
                is_merged = true;
                score_ += (*board_)[j][i];
            }
        }
    }
    return is_merged;
}

bool Game::merge_down() {
    bool is_merged = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 1; j > 0; j--) {
            if ((*board_)[j][i] == (*board_)[j - 1][i] && !(*board_)[j][i].merged && !(*board_)[j - 1][i].merged) {
                (*board_)[j][i] *= 2;
                (*board_)[j][i].merged = true;
                (*board_)[j - 1][i] = 0;
                is_merged = true;
                score_ += (*board_)[j][i];
            }
        }
    }
    return is_merged;
}

bool Game::left() {
    bool updated = false;
    updated = pull_left() || updated;
    updated = merge_left() || updated;
    updated = pull_left() || updated;
    return updated;
}

bool Game::right() {
    bool updated = false;
    updated = pull_right() || updated;
    updated = merge_right() || updated;
    updated = pull_right() || updated;
    return updated;
}

bool Game::up() {
    bool updated = false;
    updated = pull_up() || updated;
    updated = merge_up() || updated;
    updated = pull_up() || updated;
    return updated;
}

bool Game::down() {
    bool updated = false;
    updated = pull_down() || updated;
    updated = merge_down() || updated;
    updated = pull_down() || updated;
    return updated;
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
        if (is_game_win()) throw GameWinException();
        create_block();
    } else {
        delete t_prev_;
        if (is_game_over()) throw GameOverException();
    }

    return moved;
}

bool Game::restore() {
    if (!prev_board_) return false;
    *board_ = *prev_board_;
    delete prev_board_;
    prev_board_ = nullptr;
    restore_count_++;
    return true;
}

bool Game::restorable() const {
    return prev_board_ != nullptr;
}

int Game::restore_remain() const {
    return MAX_RESTORE - restore_count_;
}

std::array<Block, SIZE>& Game::operator[](int i) {
    return (*board_)[i];
}
const std::array<Block, SIZE>& Game::operator[](int i) const {
    return (*board_)[i];
}