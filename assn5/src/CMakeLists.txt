add_subdirectory(game)
add_subdirectory(ui)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/game)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ui)

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
