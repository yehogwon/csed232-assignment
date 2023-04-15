#include "artist.hpp"

artist::artist(int width, int height, const std::vector<int> &pixels)
 : width(width), height(height), pixels(pixels) { }

int artist::get_pixel(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return -1;
    return pixels[x * width + y];
}

classic::classic(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char classic::mapper(int x, int y) {
    return TOKENS[get_pixel(x, y) / 17];
}

iclassic::iclassic(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char iclassic::mapper(int x, int y) {
    return TOKENS[14 - get_pixel(x, y) / 17];
}

sobelx::sobelx(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char sobelx::mapper(int x, int y) {
    int cur = get_pixel(x, y), right = get_pixel(x + 1, y);
    if (right >= 0 && abs(cur - right) >= THRESHOLD) return '|';
    else return ' ';
}

sobely::sobely(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char sobely::mapper(int x, int y) {
    int cur = get_pixel(x, y), bottom = get_pixel(x, y + 1);
    if (bottom >= 0 && abs(cur - bottom) >= THRESHOLD) return '-';
    else return ' ';
}

gradient::gradient(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char gradient::mapper(int x, int y) {
    // TODO: Check if it works and make it fancier!
    int cur = get_pixel(x, y), right = get_pixel(x + 1, y), bottom = get_pixel(x, y + 1);
    if (right < 0 && bottom < 0) return ' ';
    // if ((bottom < 0 || (right >= 0 && bottom >= 0)) && abs(cur - right) >= THRESHOLD) return '|';
    if ((bottom < 0 || right >= 0) && abs(cur - right) >= THRESHOLD) return '|';
    // if ((right < 0 || (right >= 0 && bottom >= 0)) && abs(cur - bottom) >= THRESHOLD) return '-';
    if ((right < 0 || bottom >= 0) && abs(cur - bottom) >= THRESHOLD) return '-';
    if (right >= 0 && bottom >= 0 && abs(cur - right) >= THRESHOLD && abs(cur - bottom) >= THRESHOLD) return '+';
    return ' ';
}