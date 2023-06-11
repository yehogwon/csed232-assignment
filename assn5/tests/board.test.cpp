#include "test.h"
#include "game/board.hpp"

bool constructor_test() {
    Board board_;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) 
            if (board_[i][j].value() != 0) return false;

    return true;
}

bool index_test() {
    Board board_;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) 
            board_[i][j].value() = i + j * 3;
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) 
            if (board_[i][j].value() != i + j * 3) return false;
    
    Board board__ = board_;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) 
            if (board__[i][j].value() != i + j * 3) return false;
    
    return true;
}

bool move_test() {
    // TODO: To be implemented
    return true;
}

// TODO: test pull(), merge() : they are private methods

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        unittest("Board::Constructor", constructor_test), 
        unittest("Board::Indexing", index_test), 
        unittest("Board::Move", move_test)
    };
    return test(argv[1], tests);
}
