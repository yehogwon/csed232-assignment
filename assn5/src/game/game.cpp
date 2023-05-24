#include "game.hpp"

Game::Game() : prev_board_(nullptr), board_(new Board()), score_(0), restore_count_(0) {
    std::srand(std::time(nullptr));
    create_block(2, true);
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

bool Game::create_block(int n, bool only_two) {
    std::vector<std::pair<int, int>> empty_blocks;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == 0)
                empty_blocks.push_back(std::make_pair(i, j));
    if (empty_blocks.size() == 0) return false;
    
    int initial_size = empty_blocks.size(), n_ = n;
    std::cout << (only_two ? "INITIAL " : "GENERATE ");
    while (n_-- && empty_blocks.size() > 0) {
        int index = std::rand() % empty_blocks.size();
        empty_blocks.erase(empty_blocks.begin() + index);
        int value = std::rand() % 5 == 0 && !only_two ? 4 : 2;
        int row = empty_blocks[index].first, col = empty_blocks[index].second;
        std::cout << row + 1 << " " << col + 1 << " ";
        if (!only_two) std::cout << value << " ";
        (*board_)[row][col] = value;
    }
    std::cout << std::endl;
    return initial_size >= n;
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
                std::cout << "MERGE " << i + 1 << " " << j + 1 << " " << (*board_)[i][j] << std::endl;
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
                std::cout << "MERGE " << i + 1 << " " << j + 1 << " " << (*board_)[i][j] << std::endl;
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
                std::cout << "MERGE " << j + 1 << " " << i + 1 << " " << (*board_)[j][i] << std::endl;
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
                std::cout << "MERGE " << j + 1 << " " << i + 1 << " " << (*board_)[j][i] << std::endl;
            }
        }
    }
    return is_merged;
}

bool Game::left() {
    std::cout << "LEFT" << std::endl;
    bool updated = false;
    updated = pull<Left>() || updated;
    updated = merge_left() || updated;
    updated = pull<Left>() || updated;
    return updated;
}

bool Game::right() {
    std::cout << "RIGHT" << std::endl;
    bool updated = false;
    updated = pull<Right>() || updated;
    updated = merge_right() || updated;
    updated = pull<Right>() || updated;
    return updated;
}

bool Game::up() {
    std::cout << "UP" << std::endl;
    bool updated = false;
    updated = pull<Up>() || updated;
    updated = merge_up() || updated;
    updated = pull<Up>() || updated;
    return updated;
}

bool Game::down() {
    std::cout << "DOWN" << std::endl;
    bool updated = false;
    updated = pull<Down>() || updated;
    updated = merge_down() || updated;
    updated = pull<Down>() || updated;
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
        std::cout << "SCORE " << score_ << std::endl;
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