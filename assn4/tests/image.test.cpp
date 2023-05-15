#include "test.h"
#include "Image.h"

bool comp_(float a, float b) {
    return std::abs(a - b) < 1e-1;
}

template <typename T>
bool operator==(const RGB<T> &lhs, const RGB<T> &rhs) {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

template <>
bool operator==<float>(const RGB<float> &lhs, const RGB<float> &rhs) {
    return comp_(lhs.r, rhs.r) && comp_(lhs.g, rhs.g) && comp_(lhs.b, rhs.b);
}

template <typename T>
bool operator!=(const RGB<T> &lhs, const RGB<T> &rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool relative_comp_(const RGB<T> &lhs, const RGB<T> &rhs) {
    return std::abs(lhs.r - rhs.r) <= 2 && 
           std::abs(lhs.g - rhs.g) <= 2 &&
           std::abs(lhs.b - rhs.b) <= 2;
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

template <typename T>
bool conv_test_() {
    T val(30, 60, 90);
    HSV hsv = rgb_to_hsv(val);
    HSV ans(210, 0.6666666, 0.35924);
    return hsv == ans;
}

bool conv_test() {
    return conv_test_<RGB8b>() && conv_test_<RGBf>();
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const RGB<T> &rgb) {
    os << "(" << rgb.r << ", " << rgb.g << ", " << rgb.b << ")";
    return os;
}

bool rotation_test() {
    Image<RGBf> img(2, 2), ans(2, 2);
    img[0][0] = RGBf(30.0f, 60.0f, 90.0f);
    ans[0][0] = RGBf(90.0f, 30.0f, 60.0f);
    img[0][1] = RGBf(120.0f, 38.0f, 200.0f);
    ans[0][1] = RGBf(200.0f, 119.0f, 38.0f);
    img[1][0] = RGBf(158.0f, 84.0f, 24.0f);
    ans[1][0] = RGBf(24.0f, 158.0f, 84.0f);
    img[1][1] = RGBf(200.0f, 181.0f, 0.0f);
    ans[1][1] = RGBf(0.0f, 200.0f, 180.0f);
    img.rotate(120);
    return relative_comp_(img[0][0], ans[0][0]) && 
           relative_comp_(img[0][1], ans[0][1]) &&
           relative_comp_(img[1][0], ans[1][0]) &&
           relative_comp_(img[1][1], ans[1][1]);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("Image::Image", construct_test), 
        std::make_pair("Image::operator=", assign_test), 
        std::make_pair("Image::Memory", memory_test), 
        std::make_pair("Image::Conversion", conv_test), 
        std::make_pair("Image::Rotate", rotation_test)
    };
    return test(argv[1], tests);
}
