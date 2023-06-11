add_subdirectory(game)
add_subdirectory(ui)

add_executable(
    assn5.out
    main.cpp
)

target_link_libraries(
    assn5.out
    PRIVATE
    game.lib
    ui.lib
)

target_link_libraries(
    assn5.out
    PRIVATE
    Qt6::Widgets
)
