#ifndef __ARTIST_HPP__
#define __ARTIST_HPP__

#include <vector>

// style of ASCII art
class artist {
public: 
    /**
     * @brief A constructor for the artist class
     * @param width The width of the image
     * @param height The height of the image
     * @param pixels The pixel data of the image
    */
    artist(int width, int height, const std::vector<int> &pixels);
    
    /**
     * @brief Convert pixel to ASCII character
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    virtual char mapper(int x, int y) = 0;
};

class classic : public artist {
public:
    /**
     * @brief convert pixel to ASCII character in a classic style
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y);
};

class iclassic : public artist {
public:
    /**
     * @brief convert pixel to ASCII character in an inverted classic style
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y);
};

class sobelx : public artist {
public:
    /**
     * @brief convert pixel to ASCII character in a horizontal-edge-detection style
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y);
};

class sobely : public artist {
public:
    /**
     * @brief convert pixel to ASCII character in a vertial-edge-detection style
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y);
};

class gradient : public artist {
public:
    /**
     * @brief convert pixel to ASCII character in a gradient style (sobelx + sobely)
     * @param x x-coordinate of pixel
     * @param y y-coordinate of pixel
     * @return ASCII character to represent pixel
    */
    char mapper(int x, int y);
};

#endif