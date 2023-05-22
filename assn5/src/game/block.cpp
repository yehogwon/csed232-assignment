#include "block.hpp"

Block::Block() : value_(0), merged_(false) { }

int Block::value() const {
    return value_;
}

std::string Block::color() const {
    switch (value_) {
        case 2: return "rgb(187, 173, 160)"; break;
        case 4: return "rgb(237, 224, 200)"; break;
        case 8: return "rgb(242, 177, 121)"; break;
        case 16: return "rgb(245, 149, 99)"; break;
        case 32: return "rgb(246, 126, 95)"; break;
        case 64: return "rgb(246, 94, 59)"; break;
        case 128: return "rgb(237, 207, 114)"; break;
        case 256: return "rgb(237, 204, 97)"; break;
        case 512: return "rgb(237, 200, 80)"; break;
        case 1024: return "rgb(237, 197, 63)"; break;
        case 2048: return "rgb(237, 194, 46)"; break;
        default: return "rgb(255, 255, 255)"; break;
    }
}

bool Block::merged() const {
    return merged_;
}

void Block::clear_merged() {
    merged_ = false;
}

Block& Block::operator*=(int x) {
    value_ *= x;
    return *this;
}

void Block::operator=(int value__) {
    value_ = value__;
}

void Block::operator=(const Block& _block) {
    value_ = _block.value_;
}

bool Block::operator==(const Block& _block) const {
    return value_ == _block.value_ && value_ != 0;
}

Block::operator int() const {
    return value_;
}
