#ifndef __TEST_H__
#define __TEST_H__

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>

#define START_TEST_COUT__(BUFFER) \
    std::stringstream BUFFER; \
    std::streambuf *sbuf__ = std::cout.rdbuf(); \
    std::cout.rdbuf(BUFFER.rdbuf());
#define STOP_TEST_COUT__ \
    std::cout.rdbuf(sbuf__);

using fp = bool (*)();
using unittest = std::pair<std::string, fp>;

void show_case(std::string res, std::string ans) {
    std::cout << "Got: '''\n" << res << "\n'''\nExpected: '''\n" << ans << "\n'''" << std::endl;
}

template <typename T>
std::string typecheck(T const& t) {
    return __PRETTY_FUNCTION__;
}

bool cout_test(std::vector <std::string> answer_, std::function<void(void)> perform_) {
    START_TEST_COUT__(cout_)
    perform_();
    STOP_TEST_COUT__

    std::string answer__;
    for (const auto &s : answer_) answer__ += s + "\n";
    if (cout_.str() != answer__) {
        std::cout << "ANSWER {\n" << answer__ << "\n} but GOT {\n" << cout_.str() << "\n}";
        return false;
    } else
        return true;
}

int test(char *test_name, const std::vector<unittest> &tests) {
    for (const auto &test : tests) {
        if (test.first != test_name) continue;
        return !test.second();
    }

    return 1; // invalid test name
}


#endif // __TEST_H__