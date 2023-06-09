#include "test.h"
// #define private public // FIXME: it does not work for system header files
#include "game/game.hpp"
#undef private

bool create_test() {
    // TODO: To be implemented
    return true;
}

bool pull_test() {
    // TODO: To be implemented
    return true;
}

bool merge_test() {
    // TODO: To be implemented
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
        std::make_pair("Game::Create", create_test), 
        std::make_pair("Game::Pull", pull_test), 
        std::make_pair("Game::Merge", merge_test), 
        std::make_pair("Game::Move", move_test), 
        std::make_pair("Game::PreviousBoard", prev_test), 
        std::make_pair("Game::WinOver", win_over_test)
    };
    return test(argv[1], tests);
}
