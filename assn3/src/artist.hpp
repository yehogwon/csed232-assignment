#ifndef __ARTIST_HPP__
#define __ARTIST_HPP__

#include <vector>

const int PIXEL_MIN = 0; // minimum value of pixel
const int PIXEL_MAX = 255; // maximum value of pixel

// 15 tokens (English alphabet + special characters) sorted in order of decreasing density
const char TOKENS[] = {'@', '&', '%', 'W', 'X', 'A', 'H', 'O', 'T', '*', '^', '+', '-', '.', ' '};
const int TOKEN_SIZE = 15;

// 10 decimal digits sorted in order of decreasing density
const char DIGITS[] = {'8', '9', '6', '0', '5', '3', '2', '4', '7', '1'};
const int DIGIT_SIZE = 10;

const int THRESHOLD = 50; // threshold for edge detection (sobelx and sobely)

// style of ASCII art
class artist {
private: 
    int width; // width of image
    int height; // height of image
    const std::vector<int> &pixels; // pixel values of image

protected: 
    /**
     * @brief get pixel value at (x, y) (data hiding)
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return pixel value at (x, y)
    */
    int get_pixel(int x, int y) const;

public: 
    /**
     * @brief A constructor for the artist class
     * @param width The width of the image
     * @param height The height of the image
     * @param pixels The pixel data of the image
    */
    artist(int width, int height, const std::vector<int> &pixels);

    /**
     * @brief A destructor for the artist class (virtual)
    */
    virtual ~artist();

    /**
     * @brief get width of image (data hiding)
     * @return width of image
    */
    int get_width() const;

    /**
     * @brief get height of image (data hiding)
     * @return height of image
    */
    int get_height() const;
    
    /**
     * @brief Convert pixel to ASCII character
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    virtual char mapper(int x, int y) const = 0;
};

class classic : public artist {
public:
    /**
     * @brief A constructor for the classic class
     * @param width The width of the image
     * @param height The height of the image
     * @param pixels The pixel data of the image
    */
    classic(int width, int height, const std::vector<int> &pixels);

    /**
     * @brief convert pixel to ASCII character in a classic style
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y) const;
};

class iclassic : public artist {
public:
    /**
     * @brief A constructor for the iclassic class
     * @param width The width of the image
     * @param height The height of the image
     * @param pixels The pixel data of the image
    */
    iclassic(int width, int height, const std::vector<int> &pixels);

    /**
     * @brief convert pixel to ASCII character in an inverted classic style
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y) const;
};

class sobelx : public artist {
public:
    /**
     * @brief A constructor for the soblex class
     * @param width The width of the image
     * @param height The height of the image
     * @param pixels The pixel data of the image
    */
    sobelx(int width, int height, const std::vector<int> &pixels);

    /**
     * @brief convert pixel to ASCII character in a horizontal-edge-detection style
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y) const;
};

class sobely : public artist {
public:
    /**
     * @brief A constructor for the sobely class
     * @param width The width of the image
     * @param height The height of the image
     * @param pixels The pixel data of the image
    */
    sobely(int width, int height, const std::vector<int> &pixels);

    /**
     * @brief convert pixel to ASCII character in a vertial-edge-detection style
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y) const;
};

class gradient : public artist {
public:
    /**
     * @brief A constructor for the gradient class
     * @param width The width of the image
     * @param height The height of the image
     * @param pixels The pixel data of the image
    */
    gradient(int width, int height, const std::vector<int> &pixels);

    /**
     * @brief convert pixel to ASCII character in a gradient style (sobelx + sobely)
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y) const;
};

class digit : public artist {
public: 
    /**
     * @brief A constructor for the digit class
     * @param width The width of the image
     * @param height The height of the image
     * @param pixels The pixel data of the image
    */
    digit(int width, int height, const std::vector<int> &pixels);

    /**
     * @brief convert pixel to ASCII character in a digit style
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y) const;
};

/**
 * @brief find the min of a and b
 * @param a
 * @param b
 * @return the min of a and b
*/
template <typename T>
inline T min(T a, T b) {
    return (a < b) ? a : b;
}

/**
 * @brief find the max of a and b
 * @param a
 * @param b
 * @return the max of a and b
*/
template <typename T>
inline T max(T a, T b) {
    return (a > b) ? a : b;
}

/**
 * @brief get absolute value of a
 * @param a number
 * @return the absolute value of a
*/
template <typename T>
inline T abs(T a) {
    return a < 0 ? -a : a;
}

#endif