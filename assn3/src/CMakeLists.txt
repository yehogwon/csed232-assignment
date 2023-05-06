add_executable(
    assn3.out
    parser.cpp
    drawer.cpp
    artist.cpp
    main.cpp
)

add_library(
    assn3.lib
    STATIC
    parser.cpp
    drawer.cpp
    artist.cpp
)
