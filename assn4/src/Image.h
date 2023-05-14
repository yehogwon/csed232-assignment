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
};

// ======= ADD CODE HERE IF NEEDED =========


// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst);
void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst);

bool load_bmp(const char* path, Image<RGB8b>& img);
bool save_bmp(const char* path, const Image<RGB8b>& img);

#endif
