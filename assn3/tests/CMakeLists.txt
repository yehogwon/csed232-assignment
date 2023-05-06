get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR}/src)

get_filename_component(ROOT_DIR ../../ ABSOLUTE)
include_directories(${ROOT_DIR}/include)

add_executable(
    parser.test.out
    parser.test.cpp
)

add_executable(
    drawer.test.out
    drawer.test.cpp
)

add_executable(
    artist.test.out
    artist.test.cpp
)

target_link_libraries(parser.test.out assn3.lib)
target_link_libraries(drawer.test.out assn3.lib)
target_link_libraries(artist.test.out assn3.lib)
