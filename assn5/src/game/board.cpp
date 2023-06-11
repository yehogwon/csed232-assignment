#include "board.hpp"

Board::Board() { }

Board::Board(const Board& board) {
    board_ = board.board_; // copy constructor; copy the 2d array of blocks
}

void Board::clear_merged() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            (board_)[i][j].merged = false; // set merged to false (clear merged flag)
}

Board& Board::operator=(const Board& board) {
    board_ = board.board_; // copy assignment operator; copy the 2d array of blocks
    return *this;
}

std::array<Block, SIZE>& Board::operator[](int i) {
    return board_[i]; // return the ith row of board_
}

const std::array<Block, SIZE>& Board::operator[](int i) const {
    return board_[i]; // return the ith row of board_ (const)
}
