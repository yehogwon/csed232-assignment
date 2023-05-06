add_subdirectory(
    src
    build
)

include(CTest)

add_test(
    NAME ASSN1::prob3::operation
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tests/prob3.test.py $<TARGET_FILE:assn1_p3.out>
)
