#ifndef __TEST_H__
#define __TEST_H__

#include <string>
#include <vector>

#ifdef _TEST_COUT__
#include <iostream>
#define __IOSTREAM_INCLUDED__
#endif

#define START_TEST_COUT__(BUFFER) \
    std::stringstream BUFFER; \
    std::streambuf *sbuf__ = std::cout.rdbuf(); \
    std::cout.rdbuf(BUFFER.rdbuf());
#define STOP_TEST_COUT__ \
    std::cout.rdbuf(sbuf__);

using fp = bool (*)();

#ifdef __IOSTREAM_INCLUDED__ // To use this test function, define TEST_COUT__ first
void show_case(std::string res, std::string ans) {
    std::cout << "Got: '''\n" << res << "\n'''\nExpected: '''\n" << ans << "\n'''" << std::endl;
}
#endif

int test(char *test_name, const std::vector<std::pair<std::string, fp>> &tests) {
    for (const auto &test : tests) {
        if (test.first != test_name) continue;
        return !test.second();
    }

    return 1; // invalid test name
}

#endif // __TEST_H__