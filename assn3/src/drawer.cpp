#include "drawer.hpp"

drawer::drawer(artist *artist_) : artist_(artist_) { }

std::string drawer::draw() {
    std::stringstream oss;
    for (int i = 0; i < artist_->get_height(); i++) {
        for (int j = 0; j < artist_->get_width(); j++)
            oss << artist_->mapper(j, i);
        oss << "\n";
    }
    return oss.str();
}

downsample::downsample(artist *artist_) : drawer(artist_) { }

std::string downsample::draw() {
    std::stringstream oss;
    for (int i = 0; i < artist_->get_height(); i += 2) {
        for (int j = 0; j < artist_->get_width(); j += 2)
            oss << artist_->mapper(j, i);
        oss << "\n";
    }
    return oss.str();
}

upsample::upsample(artist *artist_) : drawer(artist_) { }

std::string upsample::draw() {
    std::stringstream oss;
    for (int i = 0; i < artist_->get_height() * 2; i++) {
        for (int j = 0; j < artist_->get_width() * 2; j++)
            oss << artist_->mapper(j / 2, i / 2);
        oss << "\n";
    }
    return oss.str();
}

scale::scale(artist *artist_, int x_ratio, int y_ratio)
 : drawer(artist_), x_ratio(x_ratio), y_ratio(y_ratio) { }

std::string scale::draw() {
    std::stringstream oss;
    
    int i_length_factor = std::abs(min(-1, y_ratio));
    int i_max = artist_->get_height() * i_length_factor;
    int i_step = std::abs(max(1, -y_ratio));

    int j_length_factor = std::abs(min(-1, x_ratio));
    int j_max = artist_->get_width() * j_length_factor;
    int j_step = std::abs(max(1, -x_ratio));

    for (int i = 0; i < i_max; i += i_step) {
        for (int j = 0; j < j_max; j += j_step)
            oss << artist_->mapper(j / j_length_factor, i / i_length_factor);
        oss << "\n";
    }
    return oss.str();
}
