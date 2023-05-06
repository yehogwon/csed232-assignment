#include "test.h"
#include "drawer.hpp"

bool drawer_test() {
    return true;
}

bool downsample_test() {
    return true;
}

bool upsample_test() {
    return true;
}

bool scale_test() {
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("drawer::drawer", drawer_test),
        std::make_pair("drawer::downsample", downsample_test),
        std::make_pair("drawer::upsample", upsample_test),
        std::make_pair("drawer::scale", scale_test)
    };
    return test(argv[1], tests);
}
