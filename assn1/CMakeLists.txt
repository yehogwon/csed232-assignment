if (POLICY CMP0025)
cmake_policy(SET CMP0025 NEW)
endif()

project("ASSN1")
cmake_minimum_required(VERSION 3.10)

enable_testing()

add_subdirectory(prob1_20220358)
add_subdirectory(prob2_20220358)
add_subdirectory(prob3_20220358)
