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

function(student_test test_name)
    add_test(
        NAME ASSN2::Student::${test_name}
        COMMAND build/tests/student.test.out Student::${test_name}
    )
endfunction(student_test)

function(node_test test_name)
    add_test(
        NAME ASSN2::Node::${test_name}
        COMMAND build/tests/node.test.out Node::${test_name}
    )
endfunction(node_test)

function(list_test test_name)
    add_test(
        NAME ASSN2::List::${test_name}
        COMMAND build/tests/list.test.out List::${test_name}
    )
endfunction(list_test)

function(io_test test_name)
    add_test(
        NAME ASSN2::Format::${test_name}
        COMMAND build/tests/io.test.out Format::${test_name}
    )
endfunction(io_test)

student_test(Student)
student_test(operator<<)
student_test(Equality)
student_test(LTGT)

node_test(Equality)
node_test(Swap)

list_test(Add)
list_test(Remove)
list_test(In)
list_test(Sort)
list_test(PivotTable)
list_test(to_string)
list_test(max)
list_test(min)

io_test(strict_input)
io_test(range_input)
io_test(input_again)
