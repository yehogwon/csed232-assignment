#include "test.h"
#include "artist.hpp"

bool classic_test() {
    return true;
}

bool iclassic_test() {
    return true;
}

bool sobelx_test() {
    return true;
}

bool sobely_test() {
    return true;
}

bool gradient_test() {
    return true;
}

bool digit_test() {
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("artist::classic", classic_test), 
        std::make_pair("artist::iclassic", iclassic_test),
        std::make_pair("artist::sobelx", sobelx_test),
        std::make_pair("artist::sobely", sobely_test),
        std::make_pair("artist::gradient", gradient_test),
        std::make_pair("artist::digit", digit_test)
    };
    return test(argv[1], tests);
}
