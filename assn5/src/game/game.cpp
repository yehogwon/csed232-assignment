#include "game.hpp"

Game::Game() : prev_board_(nullptr), board_(new Board()) { }

Game::~Game() {
    if (prev_board_)
        delete prev_board_;
    delete board_;
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

void Game::left() {
    create_block();
}

void Game::right() {
    create_block();
}

void Game::up() {
    create_block();
}

void Game::down() {
    create_block();
}

std::array<Block, SIZE>& Game::operator[](int i) {
    return (*board_)[i];
}
const std::array<Block, SIZE>& Game::operator[](int i) const {
    return (*board_)[i];
}