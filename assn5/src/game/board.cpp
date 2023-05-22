#include "board.hpp"

Board::Board() { }

std::array<Block, SIZE>& Board::operator[](int i) {
    return board_[i];
}

const std::array<Block, SIZE>& Board::operator[](int i) const {
    return board_[i];
}
