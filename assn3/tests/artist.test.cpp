#include "test.h"
#include "artist.hpp"

template<typename artist_, int W, int H>
bool artist_test(const std::vector<int> &vals, const std::vector<char> &ans) {
    if (vals.size() != W * H || ans.size() != W * H) return false;
    artist_ a(W, H, vals);
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (a.mapper(j, i) != ans[i * W + j])
                return false;
    return true;
}

bool classic_test() {
    std::vector<int> vals = {
        0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 
        16, 33, 50, 67, 84, 101, 118, 135, 152, 169, 186, 203, 220, 237, 255
    };
    std::vector<char> ans = {
        '@', '&', '%', 'W', 'X', 'A', 'H', 'O', 'T', '*', '^', '+', '-', '.', ' ', 
        '@', '&', '%', 'W', 'X', 'A', 'H', 'O', 'T', '*', '^', '+', '-', '.', ' '
    };
    return artist_test<classic, 15, 2>(vals, ans);
}

bool iclassic_test() {
    std::vector<int> vals = {
        0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 
        16, 33, 50, 67, 84, 101, 118, 135, 152, 169, 186, 203, 220, 237, 255
    };
    std::vector<char> ans = {
        ' ', '.', '-', '+', '^', '*', 'T', 'O', 'H', 'A', 'X', 'W', '%', '&', '@', 
        ' ', '.', '-', '+', '^', '*', 'T', 'O', 'H', 'A', 'X', 'W', '%', '&', '@'
    };
    return artist_test<iclassic, 15, 2>(vals, ans);
}

bool sobelx_test() {
    std::vector<int> vals = {100, 160, 120, 100, 30, 100, 100, 100, 170};
    std::vector<char> ans = {'|', ' ', ' ', '|', '|', ' ', ' ', '|', ' '};
    return artist_test<sobelx, 3, 3>(vals, ans);
}

bool sobely_test() {
    std::vector<int> vals = {100, 160, 120, 100, 30, 100, 100, 100, 170};
    std::vector<char> ans = {' ', '-', ' ', ' ', '-', '-', ' ', ' ', ' '};
    return artist_test<sobely, 3, 3>(vals, ans);
}

bool gradient_test() {
    std::vector<int> vals = {100, 160, 120, 100, 30, 100, 100, 100, 170};
    std::vector<char> ans = {'|', '-', ' ', '|', '+', '-', ' ', '|', ' '};
    return artist_test<gradient, 3, 3>(vals, ans);
}

bool digit_test() {
    std::vector<int> vals = {
        0, 25, 50, 75, 100, 125, 150, 175, 200, 225,
        24, 49, 74, 99, 124, 149, 174, 199, 224, 255
    };
    std::vector<char> ans = {
        '8', '9', '6', '0', '5', '3', '2', '4', '7', '1', 
        '8', '9', '6', '0', '5', '3', '2', '4', '7', '1'
    };
    return artist_test<digit, 10, 2>(vals, ans);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        unittest("artist::classic", classic_test), 
        unittest("artist::iclassic", iclassic_test),
        unittest("artist::sobelx", sobelx_test),
        unittest("artist::sobely", sobely_test),
        unittest("artist::gradient", gradient_test),
        unittest("artist::digit", digit_test)
    };
    return test(argv[1], tests);
}
