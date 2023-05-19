if (POLICY CMP0025)
cmake_policy(SET CMP0025 NEW)
endif()

project("ASSN5")
cmake_minimum_required(VERSION 3.10)

add_subdirectory(
    src
    build
)

add_subdirectory(
    tests
    build/tests
)

include(CTest)
