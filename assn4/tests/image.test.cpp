#include "test.h"
#include "Image.h"

template <typename T>
bool operator==(const RGB<T> &lhs, const RGB<T> &rhs) {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

template <typename T>
bool operator!=(const RGB<T> &lhs, const RGB<T> &rhs) {
    return !(lhs == rhs);
}

template <typename T>
T get_value() {
    throw std::invalid_argument("No type provided");
}

template <>
RGB8b get_value<RGB8b>() {
    return RGB8b(1, 2, 3);
}

template <>
RGBf get_value<RGBf>() {
    return RGBf(3.14f, 2.71f, 1.41f);
}

template<typename T>
Image<T> create_image() {
    throw std::invalid_argument("Invalid pixel type");
}

Image<RGB8b> create_image_b() {
    Image<RGB8b> img;
    if (!load_bmp("data/data.bmp", img)) throw std::runtime_error("Failed to load data/data.bmp");
    return img;
}

Image<RGBf> create_image_f() {
    Image<RGB8b> img_ = create_image_b();
    Image<RGBf> img;
    convert_pixel_type(img_, img);
    return img;
}

template <>
Image<RGB8b> create_image() {
    return create_image_b();
}

template <>
Image<RGBf> create_image() {
    return create_image_f();
}

template <typename T>
bool construct_test_() {
    // Image()
    Image<T> img;
    if (img.width() != 0 || img.height() != 0) return false;
    
    // Image(_width, _height)
    img = Image<T>(10, 20);
    if (img.width() != 10 || img.height() != 20) return false;
    try {
        img[0][0] = T();
        img[19][9] = T();
    } catch (std::exception &e) {
        return false;
    }

    // Image(_width, _height, val)
    T val = get_value<T>();
    img = Image<T>(10, 20, val);
    if (img.width() != 10 || img.height() != 20) return false;
    for (int i = 0; i < img.height(); i++)
        for (int j = 0; j < img.width(); j++)
            if (img[i][j] != val)
                return false;

    // Image(img)
    Image<T> img_(img);
    if (img.width() != img_.width() || img.height() != img_.height()) return false;
    for (int i = 0; i < img.height(); i++)
        for (int j = 0; j < img.width(); j++)
            if (img[i][j] != val)
                return false;
    
    return true;
}

bool construct_test() {
    return construct_test_<RGB8b>() && construct_test_<RGBf>();
}

template <typename T>
bool assign_test_() {
    Image<T> img = create_image<T>();
    Image<T> img_;
    img_ = img;
    if (img.width() != img_.width() || img.height() != img_.height()) return false;
    for (int i = 0; i < img.height(); i++)
        for (int j = 0; j < img.width(); j++)
            if (img[i][j] != img_[i][j])
                return false;
    return true;
}

bool assign_test() {
    return assign_test_<RGB8b>() && assign_test_<RGBf>();
}

bool memory_test() {
    // TODO: to be implemented
    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("Image::Image", construct_test), 
        std::make_pair("Image::operator=", assign_test), 
        std::make_pair("Image::MemoryManagement", memory_test)
    };
    return test(argv[1], tests);
}
