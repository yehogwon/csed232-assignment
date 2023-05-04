add_executable(
    assn2.out
    student.cpp
    node.cpp
    list.cpp
    io.cpp
    main.cpp
)

add_library(
    assn2_lib
    STATIC
    io.cpp
    list.cpp
    node.cpp
    student.cpp
)

target_include_directories(assn2_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
