if (POLICY CMP0025)
cmake_policy(SET CMP0025 NEW)
endif()

project("ASSN4")
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

function(sharedptr_test test_name)
    add_test(
        NAME ASSN4::SharedPtr::${test_name}
        COMMAND build/tests/sharedptr.test.out SharedPtr::${test_name}
    )
endfunction(sharedptr_test)

function(image_test test_name)
    add_test(
        NAME ASSN4::Image::${test_name}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/build/tests/image.test.out Image::${test_name}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )
endfunction(image_test)

sharedptr_test(SharedPtr)
sharedptr_test(CircularDependency)

image_test(Image)
image_test(operator=)
