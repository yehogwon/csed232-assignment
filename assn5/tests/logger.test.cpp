#define _TEST_COUT__
#include "test.h"
#include "game/logger.hpp"

bool initial_test() {
    return cout_test({
        "INITIAL 1 2 3 4",
        "INITIAL 1 2 1 2",
        "INITIAL 0 0 0 0"
    }, []() {
        Logger::initial(pos(1, 2), pos(3, 4));
        Logger::initial(pos(1, 2), pos(1, 2));
        Logger::initial(pos(0, 0), pos(0, 0));
    });
}

bool generate_test() {
    return cout_test({
        "GENERATE 1 2 2",
        "GENERATE 1 2 2",
        "GENERATE 1 4 4"
    }, []() {
        Logger::generate(pos(1, 2), 2);
        Logger::generate(pos(1, 2), 2);
        Logger::generate(pos(1, 4), 4);
    });
}

bool move_test() {
    return cout_test({
        "LEFT", 
        "UP", 
        "RIGHT",
        "DOWN"
    }, []() {
        Logger::move(LEFT);
        Logger::move(UP);
        Logger::move(RIGHT);
        Logger::move(DOWN);
    });
}

bool merge_test() {
    return cout_test({
        "MERGE 1 2 16",
        "MERGE 3 4 1024",
        "MERGE 2 2 2048",
        "MERGE 2 2 16",
        "MERGE 2 3 32",
        "MERGE 2 2 16",
        "MERGE 2 3 32",
        "MERGE 2 2 16",
        "MERGE 2 3 16",
        "MERGE 2 2 16",
        "MERGE 2 3 16", 
        "MERGE 2 2 16", 
        "MERGE 2 3 16",
        "MERGE 4 1 16",
        "MERGE 4 3 16",
        "MERGE 2 2 16", 
        "MERGE 2 3 16",
        "MERGE 4 1 16",
        "MERGE 4 3 16",
        "MERGE 2 2 16", 
        "MERGE 2 3 16",
        "MERGE 4 1 16",
        "MERGE 4 3 16",
        "MERGE 2 2 16", 
        "MERGE 2 3 16",
        "MERGE 4 1 16",
        "MERGE 4 3 16",
        "MERGE 2 2 16", 
        "MERGE 2 3 16",
        "MERGE 4 1 16",
        "MERGE 4 3 16"
    }, []() {
        std::vector<std::pair<pos, int>> merged_blocks;
        merged_blocks = {std::make_pair(pos(1, 2), 16)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(3, 4), 1024)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(2, 2), 2048)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(2, 2), 16), std::make_pair(pos(2, 3), 32)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(2, 3), 32), std::make_pair(pos(2, 2), 16)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(2, 2), 16), std::make_pair(pos(2, 3), 16)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(2, 3), 16), std::make_pair(pos(2, 2), 16)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(2, 2), 16), std::make_pair(pos(2, 3), 16), std::make_pair(pos(4, 1), 16), std::make_pair(pos(4, 3), 16)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(2, 3), 16), std::make_pair(pos(2, 2), 16), std::make_pair(pos(4, 1), 16), std::make_pair(pos(4, 3), 16)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(4, 1), 16), std::make_pair(pos(2, 2), 16), std::make_pair(pos(2, 3), 16), std::make_pair(pos(4, 3), 16)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(4, 3), 16), std::make_pair(pos(2, 2), 16), std::make_pair(pos(2, 3), 16), std::make_pair(pos(4, 1), 16)}; Logger::merge(merged_blocks);
        merged_blocks = {std::make_pair(pos(4, 1), 16), std::make_pair(pos(4, 3), 16), std::make_pair(pos(2, 2), 16), std::make_pair(pos(2, 3), 16)}; Logger::merge(merged_blocks);
    });
}

bool restore_test() {
    return cout_test({
        "RESTORE 1", 
        "RESTORE 2", 
        "RESTORE 3",
        "RESTORE 0"
    }, []() {
        Logger::restore(1);
        Logger::restore(2);
        Logger::restore(3);
        Logger::restore(0);
    });
}

bool score_test() {
    return cout_test({
        "SCORE 72", 
        "SCORE 39", 
        "SCORE 10399",
        "SCORE 20000048"
    }, []() {
        Logger::score(72);
        Logger::score(39);
        Logger::score(10399);
        Logger::score(20000048);
    });
}

bool print_test() {
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
        std::make_pair("Logger::ScoreTest", score_test),
        std::make_pair("Logger::operator<<", print_test)
    };
    return test(argv[1], tests);
}
