#include <vector>

using fp = bool (*)();

int test(char *test_name, const std::vector<std::pair<std::string, fp>> &tests) {
    for (const auto &test : tests) {
        if (test.first != test_name) continue;
        return !test.second();
    }

    return 1; // invalid test name
}
