#include "test.h"
#include "parser.hpp"

bool split_test() {
    return true;
}

bool load_image_test() {
    return true;
}

bool load_config_test() {
    return true;
}

bool write_result_test() {
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("parser::Split", split_test), 
        std::make_pair("parser::LoadImage", load_image_test), 
        std::make_pair("parser::LoadConfig", load_config_test), 
        std::make_pair("parser::WriteResult", write_result_test)
    };
    return test(argv[1], tests);
}
