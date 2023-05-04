if (POLICY CMP0025)
cmake_policy(SET CMP0025 NEW)
endif()

project("CSED232 ASSN")
cmake_minimum_required(VERSION 3.10)

# FIXME: This does not work: set(CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

# TODO: Deal with header files for add_executable()
add_subdirectory(assn1)
add_subdirectory(assn2)
add_subdirectory(assn3)
add_subdirectory(assn4)