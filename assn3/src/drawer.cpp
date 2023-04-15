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
    // TODO: Implement this
    return "";
}

upsample::upsample(artist *artist_) : drawer(artist_) { }

std::string upsample::draw() {
    // TODO: Implement this
    return "";
}

scale::scale(artist *artist_, int x_ratio, int y_ratio)
 : drawer(artist_), x_ratio(x_ratio), y_ratio(y_ratio) { }

std::string scale::draw() {
    // TODO: Implement this
    return "";
}
