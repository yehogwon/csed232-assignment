#include "artist.hpp"

artist::artist(int width, int height, const std::vector<int> &pixels)
 : width(width), height(height), pixels(pixels) { }

int artist::get_width() const {
    return width;
}

int artist::get_height() const {
    return height;
}

int artist::get_pixel(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return -1;
    return pixels[x + y * width];
}

classic::classic(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char classic::mapper(int x, int y) {
    return TOKENS[min(get_pixel(x, y) / 17, 14)];
}

iclassic::iclassic(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char iclassic::mapper(int x, int y) {
    return TOKENS[max(0, 14 - get_pixel(x, y) / 17)];
}

sobelx::sobelx(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char sobelx::mapper(int x, int y) {
    int cur = get_pixel(x, y), right = get_pixel(x + 1, y);
    if (right >= 0 && std::abs(cur - right) >= THRESHOLD) return '|';
    else return ' ';
}

sobely::sobely(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char sobely::mapper(int x, int y) {
    int cur = get_pixel(x, y), bottom = get_pixel(x, y + 1);
    if (bottom >= 0 && std::abs(cur - bottom) >= THRESHOLD) return '-';
    else return ' ';
}

gradient::gradient(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char gradient::mapper(int x, int y) {
    int cur = get_pixel(x, y), right = get_pixel(x + 1, y), bottom = get_pixel(x, y + 1);
    if (right < 0 && bottom < 0) return ' ';
    if (right >= 0 && bottom >= 0 && std::abs(cur - right) >= THRESHOLD && std::abs(cur - bottom) >= THRESHOLD) return '+';
    if ((bottom < 0 || right >= 0) && std::abs(cur - right) >= THRESHOLD) return '|';
    if ((right < 0 || bottom >= 0) && std::abs(cur - bottom) >= THRESHOLD) return '-';
    return ' ';
}
