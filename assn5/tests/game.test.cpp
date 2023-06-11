#include "test.h"
// #define private public // FIXME: it does not work for system header files
#include "game/game.hpp"
// #undef private

bool create_test() {
    // TODO: First off access to the private members
    return true;
}

bool pull_test() {
    // TODO: First off access to the private members
    return true;
}

bool merge_test() {
    // TODO: First off access to the private members
    return true;
}

bool move_test() {
    // TODO: To be implemented
    return true;
}

bool prev_test() {
    // TODO: To be implemented
    return true;
}

bool win_over_test() {
    // TODO: To be implemented
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        unittest("Game::Create", create_test), 
        unittest("Game::Pull", pull_test), 
        unittest("Game::Merge", merge_test), 
        unittest("Game::Move", move_test), 
        unittest("Game::PreviousBoard", prev_test), 
        unittest("Game::WinOver", win_over_test)
    };
    return test(argv[1], tests);
}
