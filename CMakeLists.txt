if (POLICY CMP0025)
cmake_policy(SET CMP0025 NEW)
endif()

project("CSED232 ASSN")
cmake_minimum_required(VERSION 3.10)

# set (CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(
    assn1
    build/assn1
)

add_subdirectory(
    assn2
    build/assn2
)

add_subdirectory(
    assn3
    build/assn3
)

add_subdirectory(
    assn4
    build/assn4
)

add_subdirectory(
    assn5
    build/assn5
)
