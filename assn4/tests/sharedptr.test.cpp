#include <iostream>
#include <sstream>
#include <memory>
#include "test.h"
#include "SharedPtr.h"

class MyClass {
private: 
    int data;
public: 
    MyClass(int data) : data(data) {
        std::cout << "CONSTRUCTOR " << data << std::endl;
    }

    ~MyClass() {
        std::cout << "DESTRUCTOR " << data << std::endl;
    }

    operator int() const {
        return data;
    }

    int get_value() const {
        return data;
    }
};

// legacy
bool __sharedptr_test() {
    std::vector<std::string> ans_set = {
        // test case (1)
        "CONSTRUCTOR 100", 
        "CONSTRUCTOR 200",
        "200",
        "100", 
        "100", 
        "Dealloc Object", 
        "DESTRUCTOR 100",
        "200", 
        "200", 
        "200",
        "CONSTRUCTOR 300",
        "300",
        "300", 
        "200", 
        "Dealloc Object",
        "DESTRUCTOR 300", 
        "Dealloc Object",
        "DESTRUCTOR 200",
        // test case (2)
        "CONSTRUCTOR 1", 
        "CONSTRUCTOR 2", 
        "CONSTRUCTOR 3",
        "Dealloc Object",
        "DESTRUCTOR 1",
        "Dealloc Object",
        "DESTRUCTOR 3",
        "Dealloc Object",
        "DESTRUCTOR 2",
        // test case (3)
        "CONSTRUCTOR 1", 
        "CONSTRUCTOR 2", 
        "Dealloc Object", 
        "DESTRUCTOR 2", 
        "Dealloc Object", 
        "DESTRUCTOR 1", 
        // test case (4)
        "CONSTRUCTOR 1", 
        "Dealloc Object",
        "DESTRUCTOR 1"
    };

    START_TEST_COUT__(cout_)
    {
        SharedPtr<MyClass> ptr1(new MyClass(100));
        SharedPtr<MyClass> ptr2(ptr1);
        SharedPtr<MyClass> ptr3;
        ptr3 = ptr2;

        ptr1 = SharedPtr<MyClass>(new MyClass(200));

        std::cout << ptr1->get_value() << std::endl;
        std::cout << (*ptr2) << std::endl;
        std::cout << ptr3->get_value() << std::endl;

        ptr2 = ptr3 = ptr1;

        std::cout << ptr1->get_value() << std::endl;
        std::cout << (*ptr2).get_value() << std::endl;
        std::cout << ptr3->get_value() << std::endl;

        const SharedPtr<MyClass> const_ptr(new MyClass(300));
        std::cout << const_ptr->get_value() << std::endl;
        std::cout << (*const_ptr) << std::endl;

        const MyClass* pp = (const MyClass*) ptr1;
        std::cout << pp->get_value() << std::endl;
    }
    {
        SharedPtr<MyClass> ptr1(new MyClass(1));
        SharedPtr<MyClass> ptr2(ptr1);
        ptr1 = SharedPtr<MyClass>(new MyClass(2));
        ptr2 = SharedPtr<MyClass>(new MyClass(3));
    }
    {
        SharedPtr<MyClass> ptr1(new MyClass(1));
        SharedPtr<MyClass> ptr2(ptr1);

        SharedPtr<MyClass> ptr3(ptr2);
        SharedPtr<MyClass> ptr4(new MyClass(2));

        ptr3 = ptr4;
    }
    {
        SharedPtr<MyClass> ptr1;
        ptr1 = SharedPtr<MyClass>(new MyClass(1));
    }
    STOP_TEST_COUT__

    std::string ans;
    for (const auto &s : ans_set) ans += s + "\n";
    return cout_.str() == ans;
}

MyClass* get_ptr(std::shared_ptr<MyClass>& ptr) {
    return ptr.get();
}

MyClass* get_ptr(SharedPtr<MyClass>& ptr) {
    return ptr;
}

template <typename T_sharedptr>
std::string sharedptr_test_() {
    START_TEST_COUT__(cout_)
    {
        T_sharedptr ptr1(new MyClass(100));
        T_sharedptr ptr2(ptr1);
        T_sharedptr ptr3;
        ptr3 = ptr2;

        ptr1 = T_sharedptr(new MyClass(200));

        std::cout << ptr1->get_value() << std::endl;
        std::cout << (*ptr2) << std::endl;
        std::cout << ptr3->get_value() << std::endl;

        ptr2 = ptr3 = ptr1;

        std::cout << ptr1->get_value() << std::endl;
        std::cout << (*ptr2).get_value() << std::endl;
        std::cout << ptr3->get_value() << std::endl;

        const T_sharedptr const_ptr(new MyClass(300));
        std::cout << const_ptr->get_value() << std::endl;
        std::cout << (*const_ptr) << std::endl;

        // const MyClass* pp = (const MyClass*) ptr1;
        const MyClass* pp = get_ptr(ptr1);
        std::cout << pp->get_value() << std::endl;
    }
    {
        T_sharedptr ptr1(new MyClass(1));
        T_sharedptr ptr2(ptr1);
        ptr1 = T_sharedptr(new MyClass(2));
        ptr2 = T_sharedptr(new MyClass(3));
    }
    {
        T_sharedptr ptr1(new MyClass(1));
        T_sharedptr ptr2(ptr1);

        T_sharedptr ptr3(ptr2);
        T_sharedptr ptr4(new MyClass(2));

        ptr3 = ptr4;
    }
    {
        T_sharedptr ptr1;
        ptr1 = T_sharedptr(new MyClass(1));
    }
    {
        T_sharedptr ptr1(new MyClass(123));
        T_sharedptr ptr2(ptr1);
        T_sharedptr ptr3;
        ptr1 = ptr1;
        ptr2 = ptr2;
        ptr3 = ptr3;
        ptr3 = ptr2;
    }
    STOP_TEST_COUT__

    std::string cur_, ret;
    while (std::getline(cout_, cur_)) {
        if (cur_ == "Dealloc Object") continue;
        ret += cur_;
    }

    return ret;
}

bool sharedptr_test() {
    std::string my = sharedptr_test_<SharedPtr<MyClass>>();
    std::string stl = sharedptr_test_<std::shared_ptr<MyClass>>();
    return my == stl;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("SharedPtr::SharedPtr", sharedptr_test)
    };
    return test(argv[1], tests);
}
