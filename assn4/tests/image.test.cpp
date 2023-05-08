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

bool construct_test() {
    return true;
}

bool assign_test() {
    Image<RGB8b> imgb = create_image_b();
    Image<RGB8b> imgb_ = imgb;
    if (imgb.width() != imgb_.width() || imgb.height() != imgb_.height()) return false;
    for (int i = 0; i < imgb.width() * imgb.height(); i++)
        if (imgb[i] != imgb_[i]) return false;
        
    Image<RGBf> imgf = create_image_f();
    Image<RGBf> imgf_ = imgf;
    if (imgf.width() != imgf_.width() || imgf.height() != imgf_.height()) return false;
    for (int i = 0; i < imgf.width() * imgf.height(); i++)
        if (imgf[i] != imgf_[i]) return false;
    
    return true;
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
