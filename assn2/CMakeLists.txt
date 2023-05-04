project("ASSN2")

add_subdirectory(
    src
    build
)

add_subdirectory(
    tests
    build/tests
)

include(CTest)
add_test(
    NAME node_test
    COMMAND build/tests/node.test.out
)