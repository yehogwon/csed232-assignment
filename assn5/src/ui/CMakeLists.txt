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
)
