#include "artist.hpp"

artist::artist(int width, int height, const std::vector<int> &pixels)
 : width(width), height(height), pixels(pixels) { }

artist::~artist() { }

int artist::get_width() const {
    return width;
}

int artist::get_height() const {
    return height;
}

int artist::get_pixel(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return -1; // out of range
    return pixels[x + y * width]; // return the pixel value
}

classic::classic(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char classic::mapper(int x, int y) const {
    return TOKENS[min(get_pixel(x, y) / (PIXEL_MAX / TOKEN_SIZE), TOKEN_SIZE - 1)]; // map pixel value to a character
    // get_pixel(x, y) may exceed the range of TOKENS, so we use min() to prevent it (due to the responsibility of the last token)
}

iclassic::iclassic(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char iclassic::mapper(int x, int y) const {
    return TOKENS[(TOKEN_SIZE - 1) - min(get_pixel(x, y) / (PIXEL_MAX / TOKEN_SIZE), TOKEN_SIZE - 1)]; // map pixel value to a character (reversed order of classic::mapper())
}

sobelx::sobelx(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char sobelx::mapper(int x, int y) const {
    int cur = get_pixel(x, y), right = get_pixel(x + 1, y); // current pixel and right adjacent pixel
    if (right >= 0 && abs(cur - right) >= THRESHOLD) return '|'; // if the difference is large enough (THRESHOLD), return '|' (only when the right adjacent pixel is in range)
    else return ' '; // otherwise return ' '
}

sobely::sobely(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char sobely::mapper(int x, int y) const {
    int cur = get_pixel(x, y), bottom = get_pixel(x, y + 1); // current pixel and bottom adjacent pixel
    if (bottom >= 0 && abs(cur - bottom) >= THRESHOLD) return '-'; // if the difference is large enough (THRESHOLD), return '-' (only when the bottom adjacent pixel is in range)
    else return ' '; // otherwise return ' '
}

gradient::gradient(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char gradient::mapper(int x, int y) const {
    int cur = get_pixel(x, y), right = get_pixel(x + 1, y), bottom = get_pixel(x, y + 1); // current pixel, right adjacent pixel and bottom adjacent pixel
    if (right < 0 && bottom < 0) return ' '; // right bottom corner -> ' '
    if (right >= 0 && bottom >= 0 && abs(cur - right) >= THRESHOLD && abs(cur - bottom) >= THRESHOLD) return '+'; // there are both right and bottom adjacent pixels, and the difference is large enough (THRESHOLD) -> '+'
    if (right >= 0 && abs(cur - right) >= THRESHOLD) return '|'; // there is only right adjacent pixel, and the difference is large enough (THRESHOLD) -> '|'
    if (bottom >= 0 && abs(cur - bottom) >= THRESHOLD) return '-'; // there is only bottom adjacent pixel, and the difference is large enough (THRESHOLD) -> '-'
    return ' '; // otherwise return ' '
}

digit::digit(int width, int height, const std::vector<int> &pixels)
 : artist(width, height, pixels) { }

char digit::mapper(int x, int y) const {
    return DIGITS[min(get_pixel(x, y) / (255 / DIGIT_SIZE), DIGIT_SIZE - 1)]; // map pixel value to a character (0-9 decimal digits)
}
