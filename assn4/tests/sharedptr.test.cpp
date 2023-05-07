#include "test.h"
#include "SharedPtr.h"

bool sharedptr_test() {
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("SharedPtr::SharedPtr", sharedptr_test)
    };
    return test(argv[1], tests);
}
