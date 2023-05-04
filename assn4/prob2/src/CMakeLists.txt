get_filename_component(ROOT_DIR ../../ ABSOLUTE)
include_directories(${ROOT_DIR}/prob1/src)

add_executable(
    assn4_p2.out
    Image.cc
    image_test.cc
)
