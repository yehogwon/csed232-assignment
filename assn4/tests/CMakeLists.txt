get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR}/src)

get_filename_component(ROOT_DIR ../../ ABSOLUTE)
include_directories(${ROOT_DIR}/include)

add_executable(
    sharedptr.test.out
    sharedptr.test.cpp
)

add_executable(
    image.test.out
    image.test.cpp
)

target_link_libraries(sharedptr.test.out assn4.lib)
target_link_libraries(image.test.out assn4.lib)
