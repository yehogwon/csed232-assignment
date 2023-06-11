#include "game.hpp"

Game::Game() : prev_board_(nullptr), board_(new Board()), score_(0), restore_count_(0) {
    std::srand(std::time(nullptr)); // set seed for pseudorandom
    const std::vector<std::pair<pos, int>> &&blocks__ = create_block(2, true); // create two blocks whose value is 2
    Logger::initial(blocks__[0].first, blocks__[1].first); // show initially created blocks
}

Game::~Game() {
    delete prev_board_;
    delete board_;
}

bool Game::is_game_win() const {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == GOAL) return true; // if there is a block whose value is GOAL, return true
    return false; // otherwise, return false
}

bool Game::is_game_over() const {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == 0) return false; // if there is a block whose value is 0, game is not over
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE - 1; j++)
            if ((*board_)[i][j] == (*board_)[i][j + 1]) return false; // if there is a block whose value is same with right block, game is not over
    for (int i = 0; i < SIZE - 1; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == (*board_)[i + 1][j]) return false; // if there is a block whose value is same with below block, game is not over
    return true; // otherwise, game is over
}

std::vector<std::pair<pos, int>> Game::create_block(int n, bool only_two) {
    std::vector<std::pair<int, int>> empty_blocks;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == 0)
                empty_blocks.push_back(pos(i, j)); // block with value 0 (empty) is pushed to empty_blocks (coord.)
    if (empty_blocks.size() == 0) return {}; // cannot be created
    
    std::vector<std::pair<pos, int>> blocks; // added blocks
    while (n-- && empty_blocks.size() > 0) { // while n is not 0 and empty_blocks is not empty
        int index = std::rand() % empty_blocks.size(); // randomly pick a coordinate
        empty_blocks.erase(empty_blocks.begin() + index); // erase the chosen coordinate from empty_blocks
        int value = std::rand() % 5 == 0 && !only_two ? 4 : 2; // 1/5 chance to be 4, otherwise 2
        int row = empty_blocks[index].first, col = empty_blocks[index].second; // get row and col
        blocks.push_back(std::make_pair(pos(row + 1, col + 1), value)); // push to blocks (record those added ones)
        (*board_)[row][col] = value; // set value to board
    }
    return blocks;
}

void Game::clear_merged() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            (*board_)[i][j].merged = false; // set merged to false (clear merged flag)
}

const Board& Game::prev() const {
    return *prev_board_; // return reference to prev_board_
}

const Board& Game::cur() const {
    return *board_; // return reference to board_
}

int Game::score() const {
    return score_;
}

bool Game::move(key key) {
    Board *t_prev_ = new Board(*board_); // store current board temporarily
    bool moved = false; // flag to check if it has moved
    Logger::move(key); // log that it has moved (at least, tried to move)
    // call move_<>() according to key (direction)
    switch (key) {
        case UP: moved = move_<Up>(); break;
        case DOWN: moved = move_<Down>(); break;
        case LEFT: moved = move_<Left>(); break;
        case RIGHT: moved = move_<Right>(); break;
    }
    clear_merged(); // clear merged flag

    if (moved) { // if it has been moved
        // remove previous board and update it to the temporary board
        delete prev_board_;
        prev_board_ = t_prev_;
        Logger::score(score_); // log score
        const std::vector<std::pair<pos, int>> &&blocks__ = create_block();
        Logger::generate(blocks__[0].first, blocks__[0].second); // create two blocks
        if (is_game_win()) throw GameWinException(); // if win, throw win signal
    } else {
        delete t_prev_; // it is useless
        if (is_game_over()) throw GameOverException(); // The game might be over, so check it and if so, throw game over signal
    }

    return moved; // return if it has been moved
}

bool Game::restore() {
    if (!prev_board_) return false; // if prev_board_ is nullptr (cannot be restored), return false
    *board_ = *prev_board_; // restore board (current <- previous)
    delete prev_board_; // delete previous board
    prev_board_ = nullptr; // set prev_board_ to nullptr
    restore_count_++; // One restore chance is used
    Logger::restore(restore_remain()); // show remaining restore count
    return true; // successfully restored
}

bool Game::restorable() const {
    return prev_board_ != nullptr; // return if a previous board state exists
}

int Game::restore_remain() const {
    return MAX_RESTORE - restore_count_; // return remaining restore count (total - current)
}

std::array<Block, SIZE>& Game::operator[](int i) {
    return (*board_)[i]; // return reference to board_[i] (ith row)
}
const std::array<Block, SIZE>& Game::operator[](int i) const {
    return (*board_)[i]; // return reference to board_[i] (ith row) (const)
}