#include "test.h"
#include "drawer.hpp"
#include <iostream>

const std::vector<int> VALS {
    234, 243, 36, 198, 
    216, 162, 207, 180, 
    153, 135, 198, 99, 
    234, 18, 54, 45
};

artist* make_artist() {
    return new classic(4, 4, VALS);
}

bool drawer_test() {
    drawer drawer_(make_artist());
    std::string ans = ". %+\n-*-^\n*O+A\n.&W%";
    std::string got = drawer_.draw();
    return drawer_.draw() == ans || drawer_.draw() == ans + "\n";
}

bool downsample_test() {
    downsample downsample_(make_artist());
    std::string ans = ".%\n*+";
    std::string got = downsample_.draw();
    return downsample_.draw() == ans || downsample_.draw() == ans + "\n";
}

bool upsample_test() {
    upsample upsample_(make_artist());
    std::string ans = "..  %%++\n..  %%++\n--**--^^\n--**--^^\n**OO++AA\n**OO++AA\n..&&WW%%\n..&&WW%%";
    std::string got = upsample_.draw();
    return upsample_.draw() == ans || upsample_.draw() == ans + "\n";
}

bool scale_test() {
    std::pair<std::pair<int, int>, std::string> test_cases[] {
        std::make_pair(std::make_pair(1, 1), ". %+\n-*-^\n*O+A\n.&W%"), 
        std::make_pair(std::make_pair(3, 2), "...   %%%+++\n...   %%%+++\n---***---^^^\n---***---^^^\n***OOO+++AAA\n***OOO+++AAA\n...&&&WWW%%%\n...&&&WWW%%%"), 
        std::make_pair(std::make_pair(-2, 3), ".%\n.%\n.%\n--\n--\n--\n*+\n*+\n*+\n.W\n.W\n.W"), 
        std::make_pair(std::make_pair(-2, -3), ".%\n.W")
    };

    for (auto &test_case : test_cases) {
        scale scale_(make_artist(), test_case.first.first, test_case.first.second);
        std::string got = scale_.draw();
        if (got != test_case.second && got != test_case.second + "\n")
            return false;
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        unittest("drawer::drawer", drawer_test),
        unittest("drawer::downsample", downsample_test),
        unittest("drawer::upsample", upsample_test),
        unittest("drawer::scale", scale_test)
    };
    return test(argv[1], tests);
}
