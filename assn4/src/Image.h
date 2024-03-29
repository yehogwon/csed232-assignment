#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include <cmath>
#include "SharedPtr.h"

///////////////////////////////////////////////////////////////////////////
// RGB pixel type
//    Usage:
//      - RGB<float> rgb(0.5f, 0.1f, 0.3f);
//        rgb[0] = 0.2f; // or equivalently, rgb.r = 0.2f;
template<typename ValType>
struct RGB
{
    using Type = ValType; // Declare a type alias for ValType (so that it can be accessed from outside of this struct)
    union {
        ValType data[3];
        struct {
            ValType r, g, b;
        };
    };

    RGB() {}
    RGB(ValType r_, ValType g_, ValType b_) : r(r_), g(g_), b(b_) {}

    ValType operator[](int idx) const { return data[idx]; }
    ValType& operator[](int idx) { return data[idx]; }
};

typedef RGB<uint8_t>	RGB8b;
typedef RGB<float>		RGBf;

typedef RGB<float> HSV; // alias for HSV pixel type

template <typename T>
T max(T a, T b, T c) {
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

template <typename T>
T min(T a, T b, T c) {
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

/**
 * @tparam T type of RGB pixel value (e.g., float, int)
 * @param rgb RGB pixel value
 * @return HSV pixel value
*/
template <typename T> // Template is used to support both RGB8b (i.e., RGB<uint8_t>) and RGBf (i.e., RGB<float>)
HSV rgb_to_hsv(const RGB<T> &rgb) {
    HSV hsv; // HSV to be returned
    float r = rgb.r / 255.0, g = rgb.g / 255.0, b = rgb.b / 255.0; // scaled r, g, b
    float &h = hsv[0], &s = hsv[1], &v = hsv[2]; // decalre references to easily access to h, s, v
    /* Apply the formula of converting RGB to HSV */
    float max_ = max(r, g, b);
    float min_ = min(r, g, b);
    float delta = max_ - min_;
    
    v = max_; // v is simply computed by the maximum value of r, g, b
    if (delta == 0) s = 0;
    else s = delta / max_;

    if (delta == 0) h = 0;
    else if (max_ == r) h = 60 * std::fmod((g - b) / delta, 6);
    else if (max_ == g) h = 60 * ((b - r) / delta + 2);
    else h = 60 * ((r - g) / delta + 4);

    return hsv;
}

/**
 * @tparam T type of HSV pixel value (e.g., float, int)
 * @param hsv HSV pixel value
 * @return RGB pixel value
*/
template <typename T> // Template is used to support both RGB8b (i.e., RGB<uint8_t>) and RGBf (i.e., RGB<float>)
RGB<T> hsv_to_rgb(const HSV &hsv) {
    RGB<T> rgb; // RGB to be returned
    T &r = rgb.r, &g = rgb.g, &b = rgb.b; // decalre references to easily access to r, g, b
    /* Apply the formula of converting HSV to RGB */
    float h = hsv[0], s = hsv[1], v = hsv[2];
    float c = v * s; // temporary variable for calculating r, g, b
    float x = c * (1 - std::abs(std::fmod(h / 60, 2.0f) - 1));
    float m = v - c; // temporary variable for calculating r, g, b
    float r_, g_, b_; // r, g, b value before scaling and shifting (kind of raw)
    if (h < 60) {
        r_ = c;
        g_ = x;
        b_ = 0;
    }
    else if (h < 120) {
        r_ = x;
        g_ = c;
        b_ = 0;
    }
    else if (h < 180) {
        r_ = 0;
        g_ = c;
        b_ = x;
    }
    else if (h < 240) {
        r_ = 0;
        g_ = x;
        b_ = c;
    }
    else if (h < 300) {
        r_ = x;
        g_ = 0;
        b_ = c;
    }
    else {
        r_ = c;
        g_ = 0;
        b_ = x;
    }
    r = (r_ + m) * 255; // shift and scale
    g = (g_ + m) * 255; // shift and scale
    b = (b_ + m) * 255; // shift and scale
    return rgb;
}

///////////////////////////////////////////////////////////////////////////
// Image class template
//
template<typename PixelType>
class Image
{
private:
    // ======= ADD CODE HERE IF NEEDED =========
    using PixelArray = SharedPtr<PixelType, ArrayDeallocator<PixelType>>;

    size_t m_width, m_height;
    PixelArray m_buff;
    
public:
    ////////////////////////////////////////////
    // constructors & destructor
    ////////////////////////////////////////////
    
    // constructor without argument -> create an empty image (zero by zero)
    Image<PixelType>() : m_width(0), m_height(0) { }

    // constructor with width and height -> create an image with given width and height
    Image<PixelType>(size_t _width, size_t _height) : m_width(_width), m_height(_height), m_buff(new PixelType[_width * _height]) { }

    // constructor with width, height, and initial value -> create an image with given width and height, and fill the image with the given value
    Image<PixelType>(size_t _width, size_t _height, const PixelType &val) : m_width(_width), m_height(_height), m_buff(new PixelType[_width * _height]) {
        for (size_t i = 0; i < m_width * m_height; i++) m_buff[i] = val; // traverse the image and fill it with the given value
    }

    // copy constructor -> create an image with the same width, height, and pixel values as the given image
    Image<PixelType>(const Image<PixelType> &img) : m_width(img.width()), m_height(img.height()), m_buff(new PixelType[img.width() * img.height()]) {
        for (size_t i = 0; i < m_width * m_height; i++) m_buff[i] = img.m_buff[i]; // copy the pixel values from the source image
    }

    ~Image<PixelType>() { } // destructor does nothing since SharedPtr automatically handles memory deallocation

    ////////////////////////////////////////////
    // assignment operator
    ////////////////////////////////////////////
    
    Image<PixelType>& operator=(const Image<PixelType> &img) {
        if (*this == img) return *this; // if the source image is the same as the destination image (assigning itself), return right away
        m_width = img.width(), m_height = img.height(); // copy width and height
        if (m_width * m_height == 0) return *this; // if the image is empty, return right away
        m_buff = PixelArray(new PixelType[m_width * m_height]); // allocate memory for the image
        for (size_t i = 0; i < m_width * m_height; i++) m_buff[i] = img.m_buff[i]; // copy the pixel values from the source image
        return *this;
    }

    ////////////////////////////////////////////
    // element access operators
    ////////////////////////////////////////////
    PixelType* operator[](int y) { return &m_buff[y * m_width]; }
    const PixelType* operator[](int y) const { return &m_buff[y * m_width]; }

    ////////////////////////////////////////////
    // other methods
    ////////////////////////////////////////////
    //   - width(), height()

    /**
     * @brief Get the width of the image
     * @return width of the image
    */
    size_t width() const {
        return m_width;
    }

    /**
     * @brief Get the height of the image
     * @return height of the image
    */
    size_t height() const {
        return m_height;
    }

    bool operator==(const Image<PixelType> &img) {
        return m_width == img.width() && m_height == img.height() && m_buff == img.m_buff; // compare width, height, and pixel values
    }

    void rotate(int deg) { // rotate hue
        deg %= 360; // deg must be in the range [0, 360)
        if (deg == 0 || m_width * m_height == 0) return; // there is nothing to do (no rotation or no image)
        for (size_t i = 0; i < m_width * m_height; i++) { // traverse the image pixelwisely
            HSV hsv = rgb_to_hsv(m_buff[i]); // convert the pixel value to HSV
            hsv[0] += deg % 360; // rotate the hue (modulo 360 for preventing overflow)
            /* Fit hue into the range [0, 360] */
            if (hsv[0] > 360) hsv[0] -= 360;
            if (hsv[0] < 0) hsv[0] += 360;
            RGB<typename PixelType::Type> rgb = hsv_to_rgb<typename PixelType::Type>(hsv); // convert the pixel value back to RGB
            for (int j = 0; j < 3; j++) m_buff[i][j] = rgb[j]; // assign rotated RGB values to the pixel (rotation done)
        }
    }
};

// ======= ADD CODE HERE IF NEEDED =========

// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst);
void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst);

bool load_bmp(const char* path, Image<RGB8b>& img);
bool save_bmp(const char* path, const Image<RGB8b>& img);

#endif
