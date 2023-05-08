#include "test.h"
#include "Image.h"

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

template<typename T>
Image<T> create_image() {
    throw std::invalid_argument("Invalid pixel type");
}

template <>
Image<RGB8b> create_image() {
    return create_image_b();
}

template <>
Image<RGBf> create_image() {
    return create_image_f();
}

bool construct_test() {
    return true;
}

template <typename T>
bool assign_test_() {
    Image<T> img = create_image<T>();
    Image<T> img_ = img;
    if (img.width() != img_.width() || img.height() != img_.height()) return false;
    for (int i = 0; i < img.width() * img.height(); i++)
        if (img[i] != img_[i]) return false;
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
        std::make_pair("Image::operator=", construct_test), 
        std::make_pair("Image::MemoryManagement", memory_test)
    };
    return test(argv[1], tests);
}
