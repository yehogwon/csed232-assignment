#include "node.hpp"
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
    std::pair<std::string, fp> tests[] {
        std::make_pair("Node::Equality", equal_test), 
        std::make_pair("Node::Swap", swap_test)
    };

    if (argc != 2) return 1; // invalid arguments (requires test name)
    for (const auto &test : tests) {
        if (test.first != argv[1]) continue;
        return !test.second();
    }

    return 1; // invalid test name
}
