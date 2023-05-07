#include "test.h"
#include "SharedPtr.h"
#include <sstream>

bool sharedptr_test() {
    /* Code Snippet for Catching std::cout */
    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
    // print something here
    std::cout.rdbuf(sbuf);

    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("SharedPtr::SharedPtr", sharedptr_test)
    };
    return test(argv[1], tests);
}
