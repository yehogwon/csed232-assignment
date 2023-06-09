get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR}/src)

get_filename_component(ROOT_DIR ../../ ABSOLUTE)
include_directories(${ROOT_DIR}/include)

add_executable(
    block.test.out
    block.test.cpp
)

add_executable(
    game.test.out
    game.test.cpp
)

add_executable(
    board.test.out
    board.test.cpp
)

add_executable(
    logger.test.out
    logger.test.cpp
)

target_link_libraries(block.test.out game.lib)
target_link_libraries(game.test.out game.lib)
target_link_libraries(board.test.out game.lib)
target_link_libraries(logger.test.out game.lib)
