add_subdirectory(
    src
    build
)

include(CTest)

add_test(
    NAME ASSN1::prob2::operation
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/tests/prob2.test.py $<TARGET_FILE:assn1_p2.out>
)
