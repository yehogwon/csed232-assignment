#include "board.hpp"

Board::Board() { }

Board::Board(const Board& board) {
    board_ = board.board_;
}

std::array<Block, SIZE>& Board::operator[](int i) {
    return board_[i];
}

const std::array<Block, SIZE>& Board::operator[](int i) const {
    return board_[i];
}
