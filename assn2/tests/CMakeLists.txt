get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR}/src)

get_filename_component(ROOT_DIR ../../ ABSOLUTE)
include_directories(${ROOT_DIR}/include)

add_executable(
    student.test.out
    student.test.cpp
)

add_executable(
    node.test.out
    node.test.cpp
)

add_executable(
    list.test.out
    list.test.cpp
)

add_executable(
    io.test.out
    io.test.cpp
)

target_link_libraries(node.test.out assn2.lib)
target_link_libraries(student.test.out assn2.lib)
