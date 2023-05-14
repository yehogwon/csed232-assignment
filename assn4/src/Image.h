#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include "SharedPtr.h"

///////////////////////////////////////////////////////////////////////////
// RGB pixel type
//    Usage:
//      - RGB<float> rgb(0.5f, 0.1f, 0.3f);
//        rgb[0] = 0.2f; // or equivalently, rgb.r = 0.2f;
template<typename ValType>
struct RGB
{
	using Type = ValType;
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

typedef RGB<float> HSV;

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
	Image() : m_width(0), m_height(0) { }

	// constructor with width and height -> create an image with given width and height
	Image(size_t _width, size_t _height) : m_width(_width), m_height(_height), m_buff(new PixelType[_width * _height]) { }

	// constructor with width, height, and initial value -> create an image with given width and height, and fill the image with the given value
	Image(size_t _width, size_t _height, const PixelType &val) : m_width(_width), m_height(_height), m_buff(new PixelType[_width * _height]) {
		for (size_t i = 0; i < m_width * m_height; i++) m_buff[i] = val; // traverse the image and fill it with the given value
	}

	// copy constructor -> create an image with the same width, height, and pixel values as the given image
	Image(const Image<PixelType> &img) : m_width(img.width()), m_height(img.height()), m_buff(new PixelType[img.width() * img.height()]) {
		for (size_t i = 0; i < m_width * m_height; i++) m_buff[i] = img.m_buff[i]; // copy the pixel values from the source image
	}

	~Image() { } // destructor does nothing since SharedPtr automatically handles memory deallocation

	////////////////////////////////////////////
	// assignment operator
	////////////////////////////////////////////
	
	Image& operator=(const Image &img) {
		m_width = img.width(), m_height = img.height(); // copy width and height
		if (m_width * m_height == 0) return *this; // if the image is empty, return right away
		m_buff = PixelArray(new PixelType[m_width * m_height]); // allocate memory for the image
		for (size_t i = 0; i < m_width * m_height; i++) m_buff[i] = img.m_buff[i]; // copy the pixel values from the source image
		return *this;
	}
	
	const Image& operator=(const Image &img) const {
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

	void rotate(int deg) { // rotate hue
		if (deg == 0 || m_width * m_height == 0) return;
		for (size_t i = 0; i < m_width * m_height; i++) {
			HSV hsv = rgb_to_hsv(m_buff[i]);
			hsv[0] += deg % 360;
			if (hsv[0] > 360) hsv[0] -= 360;
			if (hsv[0] < 0) hsv[0] += 360;
			RGB<typename PixelType::Type> rgb = hsv_to_rgb<typename PixelType::Type>(hsv);
			for (int j = 0; j < 3; j++) m_buff[i][j] = rgb[j];
		}
	}
};

// ======= ADD CODE HERE IF NEEDED =========
template <typename T>
HSV rgb_to_hsv(const T &rgb) {
	HSV hsv;
	float r = rgb.r, g = rgb.g, b = rgb.b;
	float &h = hsv[0], &s = hsv[1], &v = hsv[2];
	float max = std::max(r, std::max(g, b));
	float min = std::min(r, std::min(g, b));
	float delta = max - min;
	v = max;
	if (max != 0) s = delta / max;
	else s = 0;
	if (s == 0) h = 0;
	else {
		if (r == max) h = (g - b) / delta;
		else if (g == max) h = 2 + (b - r) / delta;
		else h = 4 + (r - g) / delta;
		h *= 60;
		if (h < 0) h += 360;
	}
	return hsv;
}

template <typename T>
RGB<T> hsv_to_rgb(const HSV &hsv) {
	RGB<T> rgb;
	T &r = rgb.r, &g = rgb.g, &b = rgb.b;
	float h = hsv[0], s = hsv[1], v = hsv[2];
	float c = v * s;
	float x = c * (1 - std::abs(std::fmod(h / 60, 2) - 1));
	float m = v - c;
	if (h < 60) r = c, g = x, b = 0;
	else if (h < 120) r = x, g = c, b = 0;
	else if (h < 180) r = 0, g = c, b = x;
	else if (h < 240) r = 0, g = x, b = c;
	else if (h < 300) r = x, g = 0, b = c;
	else r = c, g = 0, b = x;
	r += m, g += m, b += m;
	return rgb;
}

// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst);
void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst);

bool load_bmp(const char* path, Image<RGB8b>& img);
bool save_bmp(const char* path, const Image<RGB8b>& img);

#endif
