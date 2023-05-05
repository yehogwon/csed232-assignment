get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR}/src)

add_executable(
    node.test.out
    node.test.cpp
)

add_executable(
    student.test.out
    student.test.cpp
)

target_link_libraries(node.test.out assn2.lib)
target_link_libraries(student.test.out assn2.lib)
