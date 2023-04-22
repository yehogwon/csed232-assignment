#ifndef __ARTIST_HPP__
#define __ARTIST_HPP__

#include <vector>

const char TOKENS[] = {'@', '&', '%', 'W', 'X', 'A', 'H', 'O', 'T', '*', '^', '+', '-', '.', ' '};
const int THRESHOLD = 50;

// style of ASCII art
class artist {
private: 
    int width;
    int height;
    std::vector<int> pixels;

protected: 
    int get_pixel(int x, int y) const;
public: 
    /**
     * @brief A constructor for the artist class
     * @param width The width of the image
     * @param height The height of the image
     * @param pixels The pixel data of the image
    */
    artist(int width, int height, const std::vector<int> &pixels);

    virtual ~artist();

    int get_width() const;

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

template <typename T>
T min(T a, T b) {
    return (a < b) ? a : b;
}

template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
T abs(T a) {
    return a < 0 ? -a : a;
}

#endif