#include "game.hpp"

std::array<Block, 4>& Game::operator[](int i) {
    return board_[i];
}
const std::array<Block, 4>& Game::operator[](int i) const {
    return board_[i];
}