#ifndef __TEST_H__
#define __TEST_H__

#include <string>
#include <vector>

#define START_TEST_COUT__(BUFFER) \
    std::stringstream BUFFER; \
    std::streambuf *sbuf__ = std::cout.rdbuf(); \
    std::cout.rdbuf(BUFFER.rdbuf());
#define STOP_TEST_COUT__ \
    std::cout.rdbuf(sbuf__);

using fp = bool (*)();

int test(char *test_name, const std::vector<std::pair<std::string, fp>> &tests) {
    for (const auto &test : tests) {
        if (test.first != test_name) continue;
        return !test.second();
    }

    return 1; // invalid test name
}

#endif // __TEST_H__