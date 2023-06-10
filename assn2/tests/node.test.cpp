#include "node.hpp"
#include "test.h"
#include <sstream>

using fp = bool (*)();

void create_new_student(Student &s) {
    std::istringstream iss("CSE\nM\nKim\n23\n");
    std::ostringstream oss;
    s = Student(iss, oss);
}

bool equal_test() {
    Student a, b;
    create_new_student(a);
    Node n1(a), n2(b), n3(a);
    return !(n1 == n2) && (n1 == n3);
}

bool swap_test() {
    Student a, b;
    create_new_student(a);
    Node n1(a), n2(b);
    swap_node(&n1, &n2);
    return n1.data == b && n2.data == a;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        unittest("Node::Equality", equal_test), 
        unittest("Node::Swap", swap_test)
    };
    return test(argv[1], tests);
}
