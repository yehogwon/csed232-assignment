#include "drawer.hpp"

drawer::drawer(artist *artist_) : artist_(artist_) { }

drawer::~drawer() { }

std::string drawer::draw_helper(int i_factor, int i_step, int j_factor, int j_step) const {
    std::stringstream oss;
    for (int i = 0; i < artist_->get_height() * i_factor; i += i_step) {
        for (int j = 0; j < artist_->get_width() * j_factor; j += j_step)
            oss << artist_->mapper(j / j_factor, i / i_factor);
        oss << "\n";
    }
    return oss.str();
}

std::string drawer::draw() const {
    return draw_helper(1, 1, 1, 1);
}

downsample::downsample(artist *artist_) : drawer(artist_) { }

std::string downsample::draw() const {
    return draw_helper(1, 2, 1, 2);
}

upsample::upsample(artist *artist_) : drawer(artist_) { }

std::string upsample::draw() const {
    return draw_helper(2, 1, 2, 1);
}

scale::scale(artist *artist_, int x_ratio, int y_ratio)
 : drawer(artist_), x_ratio(x_ratio), y_ratio(y_ratio) { }

std::string scale::draw() const {
    int i_length_factor = abs(max(1, y_ratio)), i_step = abs(max(1, -y_ratio));
    int j_length_factor = abs(max(1, x_ratio)), j_step = abs(max(1, -x_ratio));
    return draw_helper(i_length_factor, i_step, j_length_factor, j_step);
}
