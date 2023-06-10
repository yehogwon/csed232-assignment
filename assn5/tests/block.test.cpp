#include "test.h"
#include "game/block.hpp"

bool constructor_test() {
    Block block_;
    if (block_.value() != 0 || block_.color() != "rgb(255, 255, 255)") return false;
    block_.value() = 16;
    Block block__ = block_;
    if (block__.value() != 16 || block__.color() != "rgb(245, 149, 99)") return false;
    
    return true;
}

bool value_test() {
    Block block_; 
    if (block_.value() != 0) return false;
    block_.value() = 16; if (block_.value() != 16) return false;
    block_.value() = 32; if (block_.value() != 32) return false;
    block_.value() = 2048; if (block_.value() != 2048) return false;
    
    return true;
}

bool color_test() {
    Block block_; 
    if (block_.color() != "rgb(255, 255, 255)") return false;
    block_.value() = 2; if (block_.color() != "rgb(187, 173, 160)") return false;
    block_.value() = 4; if (block_.color() != "rgb(237, 224, 200)") return false;
    block_.value() = 8; if (block_.color() != "rgb(242, 177, 121)") return false;
    block_.value() = 16; if (block_.color() != "rgb(245, 149, 99)") return false;
    block_.value() = 32; if (block_.color() != "rgb(246, 126, 95)") return false;
    block_.value() = 64; if (block_.color() != "rgb(246, 94, 59)") return false;
    block_.value() = 128; if (block_.color() != "rgb(237, 207, 114)") return false;
    block_.value() = 256; if (block_.color() != "rgb(237, 204, 97)") return false;
    block_.value() = 512; if (block_.color() != "rgb(237, 200, 80)") return false;
    block_.value() = 1024; if (block_.color() != "rgb(237, 197, 63)") return false;
    block_.value() = 2048; if (block_.color() != "rgb(237, 194, 46)") return false;

    return true;
}

bool multiplication_test() {
    Block block_;
    block_.value() = 32;
    block_ *= 2; 
    return block_.value() == 64;
}

bool assign_test() {
    Block block_, block__;
    block_.value() = 32;
    block__ = block_;
    return block__.value() == 32;
}

bool comparison_test() {
    Block block_, block__;
    block_.value() = 32;
    block__.value() = 32;

    Block block_0, block__0;
    block_0.value() = 0;
    block__0.value() = 0;

    return block_ == block__ && !(block_0 == block__0);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        unittest("Block::ConstructorTest", constructor_test), 
        unittest("Block::ValueTest", value_test), 
        unittest("Block::ColorTest", color_test), 
        unittest("Block::MultiplicationTest", multiplication_test), 
        unittest("Block::AssignmentTest", assign_test), 
        unittest("Block::ComparisonTest", comparison_test)
    };
    return test(argv[1], tests);
}
