#include "board.hpp"

Board::Board() { }

Board::Board(const Board& board) {
    board_ = board.board_; // copy constructor; copy the 2d array of blocks
}

std::array<Block, SIZE>& Board::operator[](int i) {
    return board_[i]; // return the ith row of board_
}

const std::array<Block, SIZE>& Board::operator[](int i) const {
    return board_[i]; // return the ith row of board_ (const)
}
