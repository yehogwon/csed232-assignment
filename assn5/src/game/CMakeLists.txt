get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

add_library(
    game.lib
    block.cpp
    block.hpp
    board.cpp
    board.hpp
    game.cpp
    game.hpp
    logger.cpp
    logger.hpp
    status.hpp
)

target_link_libraries(
    game.lib
    PRIVATE
    Qt6::Widgets
)
