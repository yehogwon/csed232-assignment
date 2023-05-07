#include "test.h"
#include "Image.h"

bool construct_test() {
    return true;
}

bool assign_test() {
    return true;
}

bool memory_test() {
    // TODO: to be implemented
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("Image::Image", construct_test), 
        std::make_pair("Image::operator=", construct_test), 
        std::make_pair("Image::MemoryManagement", memory_test)
    };
    return test(argv[1], tests);
}
