if (POLICY CMP0025)
cmake_policy(SET CMP0025 NEW)
endif()

project("ASSN5")
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(
    src
    build
)

add_subdirectory(
    tests
    build/tests
)

include(CTest)

function(block_test test_name)
    add_test(
        NAME ASSN5::Block::${test_name}
        COMMAND build/tests/block.test.out Block::${test_name}
    )
endfunction(block_test)

function(game_test test_name)
    add_test(
        NAME ASSN5::Game::${test_name}
        COMMAND build/tests/game.test.out Game::${test_name}
    )
endfunction(game_test)

function(board_test test_name)
    add_test(
        NAME ASSN5::Board::${test_name}
        COMMAND build/tests/board.test.out Board::${test_name}
    )
endfunction(board_test)

function(logger_test test_name)
    add_test(
        NAME ASSN5::Logger::${test_name}
        COMMAND build/tests/logger.test.out Logger::${test_name}
    )
endfunction(logger_test)

logger_test(InitialTest)
logger_test(GenerateTest)
logger_test(MoveTest)
logger_test(MergeTest)
logger_test(RestoreTest)
logger_test(ScoreTest)
logger_test(operator<<)

block_test(ConstructorTest)
block_test(ValueTest)
block_test(ColorTest)
block_test(MultiplicationTest)
block_test(AssignmentTest)
block_test(ComparisonTest)

board_test(Constructor)
board_test(Indexing)

game_test(Create)
game_test(Pull)
game_test(Merge)
game_test(Move)
game_test(PreviousBoard)
game_test(WinOver)
