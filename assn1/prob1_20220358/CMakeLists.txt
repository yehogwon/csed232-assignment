add_subdirectory(
    src
    build
)

include(CTest)

# command of the test below gives a argument as a build directory path (set variable)
add_test(
    NAME ASSN1::prob1::convert
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tests/prob1.test.py $<TARGET_FILE:assn1_p1.out>
)
