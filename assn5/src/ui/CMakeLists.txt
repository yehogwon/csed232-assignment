get_filename_component(PARENT_DIR ../ ABSOLUTE)
# include_directories(${PARENT_DIR}/game)

add_library(
    ui.lib
    block.ui.cpp
    block.ui.hpp
    game.ui.cpp
    game.ui.hpp
)

target_link_libraries(
    ui.lib
    PRIVATE
    Qt6::Widgets
    game.lib
)
