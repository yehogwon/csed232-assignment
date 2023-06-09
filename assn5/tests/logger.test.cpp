#include "test.h"
#include "game/logger.hpp"

bool initial_test() {
    // TODO: To be implemented
    return true;
}

bool generate_test() {
    // TODO: To be implemented
    return true;
}

bool move_test() {
    // TODO: To be implemented
    return true;
}

bool merge_test() {
    // TODO: To be implemented
    return true;
}

bool restore_test() {
    // TODO: To be implemented
    return true;
}

bool score_test() {
    // TODO: To be implemented
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("Logger::InitialTest", initial_test), 
        std::make_pair("Logger::GenerateTest", generate_test), 
        std::make_pair("Logger::MoveTest", move_test), 
        std::make_pair("Logger::MergeTest", merge_test), 
        std::make_pair("Logger::RestoreTest", restore_test), 
        std::make_pair("Logger::ScoreTest", score_test)
    };
    return test(argv[1], tests);
}
