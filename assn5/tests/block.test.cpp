#include "test.h"
#include "game/block.hpp"

bool constructor_test() {
    // TODO: To be implemented
    return true;
}

bool value_test() {
    // TODO: To be implemented
    return true;
}

bool color_test() {
    // TODO: To be implemented
    return true;
}

bool multiplication_test() {
    // TODO: To be implemented
    return true;
}

bool assign_test() {
    // TODO: To be implemented
    return true;
}

bool comparison_test() {
    // TODO: To be implemented
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("Block::ConstructorTest", constructor_test), 
        std::make_pair("Block::ValueTest", value_test), 
        std::make_pair("Block::ColorTest", color_test), 
        std::make_pair("Block::MultiplicationTest", multiplication_test), 
        std::make_pair("Block::AssignmentTest", assign_test), 
        std::make_pair("Block::ComparisonTest", comparison_test)
    };
    return test(argv[1], tests);
}
