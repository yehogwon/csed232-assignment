#include "test.h"
#include "game/board.hpp"

bool constructor_test() {
    // TODO: To be implemented
    return true;
}

bool index_test() {
    // TODO: To be implemented
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("Board::Constructor", constructor_test), 
        std::make_pair("Board::Indexing", index_test)
    };
    return test(argv[1], tests);
}
