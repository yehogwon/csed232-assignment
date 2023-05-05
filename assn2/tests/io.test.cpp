#include "io.hpp"
#include "test.h"
#include <sstream>

bool strict_test() {
    return true;
}

bool range_test() {
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("Format::strict_input", strict_test), 
        std::make_pair("Format::range_input", range_test)
    };
    return test(argv[1], tests);
}
