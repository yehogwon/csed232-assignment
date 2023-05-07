#define _TEST_COUT__
#include <iostream>
#include <sstream>
#include "test.h"
#include "SharedPtr.h"

class MyClass {
public: 
    MyClass() {
        std::cout << "CONSTRUCTOR" << std::endl;
    }

    ~MyClass() {
        std::cout << "DESTRUCTOR" << std::endl;
    }
};

bool sharedptr_test() {
    std::vector<std::string> ans_set = {
        "CONSTRUCTOR", 
        "Dealloc Object", 
        "DESTRUCTOR"
    };

    START_TEST_COUT__(cout_)
    {
        SharedPtr<MyClass> ptr1(new MyClass());
        SharedPtr<MyClass> ptr2(ptr1);
    }
    STOP_TEST_COUT__

    std::string ans;
    for (const auto &s : ans_set) ans += s + "\n";
    
    return cout_.str() == ans;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("SharedPtr::SharedPtr", sharedptr_test)
    };
    return test(argv[1], tests);
}
