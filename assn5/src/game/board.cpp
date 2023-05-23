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

std::ostream& operator<<(std::ostream& os, const Board& board) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            os << std::setw(4) << board[i][j].value() << " ";
        }
        os << std::endl;
    }
    return os;
}
