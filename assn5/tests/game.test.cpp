#include "test.h"
#include "game/game.hpp"

// TODO: test create_block() : they are private methods

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
        unittest("Game::Move", move_test), 
        unittest("Game::PreviousBoard", prev_test), 
        unittest("Game::WinOver", win_over_test)
    };
    return test(argv[1], tests);
}
