add_executable(
    assn2.out
    student.cpp
    node.cpp
    list.cpp
    io.cpp
    main.cpp
)

add_library(
    assn2.lib
    STATIC
    io.cpp
    list.cpp
    node.cpp
    student.cpp
)
