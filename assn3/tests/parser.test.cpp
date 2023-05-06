#include "test.h"
#include "parser.hpp"
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>

bool load_image_test() {
    std::pair<std::string, std::vector<int>> test_cases[] {
        std::make_pair("data/input1.txt", std::vector<int> {169, 2, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 253, 254, 254, 254, 251, 254, 241, 254, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 251, 233, 77, 49, 37, 55, 77, 33, 24, 77, 31, 143, 143, 179, 247, 251, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 247, 95, 107, 24, 40, 24, 41, 55, 77, 24, 46, 55, 95, 36, 27, 37, 49, 27, 130, 251, 251, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 251, 251, 85, 37, 41, 27, 31, 29, 36, 40, 27, 36, 46, 18, 15, 31, 63, 24, 85, 77, 70, 77, 55, 46, 247, 251, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 251}), 
        std::make_pair("data/input2.txt", std::vector<int> {3, 3, 100, 160, 120, 100, 30, 100, 100, 100, 170})
    };

    parser p;
    for (auto &test_case : test_cases) {
        std::vector<int> result = p.load_image(test_case.first.c_str());
        if (result != test_case.second) return false;
    }
    return true;
}

bool load_config_test() {
    std::pair<std::string, std::vector<std::string>> test_cases[] {
        std::make_pair("data/config1.txt", std::vector<std::string> {"classic", "drawer"}), 
        std::make_pair("data/config2.txt", std::vector<std::string> {"iclassic", "scale", "1", "-2"}), 
        std::make_pair("data/config3.txt", std::vector<std::string> {"gradient", "drawer"}), 
        std::make_pair("data/config4.txt", std::vector<std::string> {"classic", "scale", "3", "-2"}), 
        std::make_pair("data/config5.txt", std::vector<std::string> {"sobelx", "scale", "-5", "-2"}), 
        std::make_pair("data/config6.txt", std::vector<std::string> {"sobely", "scale", "25", "34"})
    };

    parser p;
    for (auto &test_case : test_cases) {
        std::vector<std::string> result = p.load_config(test_case.first.c_str());
        if (result != test_case.second) return false;
    }
    return true;
}

bool write_result_test() {
    std::string test_cases[] {
        "lllaksjkdjf", 
        "lllaksjkdjf\n", 
        "saladsf\nasdlalksdf", 
        "saladsf\nasdlalksdf\n"
    };

    parser p;
    char *file_name;
    for (const std::string &test_case : test_cases) {
        std::string file_name = "/tmp/assn3.parser.test.write_result." + std::to_string(std::rand());
        p.write_result(file_name.c_str(), test_case);
        std::ifstream in_file(file_name);
        std::string result;
        std::getline(in_file, result, '\0');
        std::remove(file_name.c_str());
        if (result != test_case)
            return false;
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("parser::LoadImage", load_image_test), 
        std::make_pair("parser::LoadConfig", load_config_test), 
        std::make_pair("parser::WriteResult", write_result_test)
    };
    return test(argv[1], tests);
}
