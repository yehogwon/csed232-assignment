#include <iostream>
#include "parser.hpp"
#include "artist.hpp"
#include "drawer.hpp"

/* Questions
 * Is it fine to append std:: prefix to vector even though it is not allowed to edit main function?
 * Is it fine to make artist classs abstract?
 * Is it okay to rename the variables `artist` in drawer class due to the ambiguity?
 */

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "argc is not 4, but " << argc << std::endl;
        throw;
    }
    
    // CREATE PARSER
    parser p;

    // LOAD IMAGE AND CONFIG
    std::vector<int> tokens = p.load_image(argv[1]);
    std::vector<std::string> configs = p.load_config(argv[2]);
    std::string style_target = configs[0];
    std::string drawer_target = configs[1];
    char *path_output = argv[3];

    int width = tokens[0];
    int height = tokens[1];
    std::vector<int> vals = {tokens.begin() + 2, tokens.end()};

    // CREATE ARTIST
    artist *style;
    if (style_target == "classic") {
        style = new classic(width, height, vals);
    } else if (style_target == "iclassic") {
        style = new iclassic(width, height, vals);
    } else if (style_target == "sobelx") {
        style = new sobelx(width, height, vals);
    } else if (style_target == "sobely") {
        style = new sobely(width, height, vals);
    } else if (style_target == "gradient") {
        style = new gradient(width, height, vals);
    } else {
        throw;
    }

    // CREATE DRAWER
    drawer *d;
    if (drawer_target == "drawer") {
        d = new drawer(style);
    } else if (drawer_target == "upsample") {
        d = new upsample(style);
    } else if (drawer_target == "downsample") {
        d = new downsample(style);
    } else if (drawer_target == "scale") {
        int scale_x = stoi(configs[2]);
        int scale_y = stoi(configs[3]);
        d = new scale(style, scale_x, scale_y);
    } else {
        throw;
    }

    // PERFORM DRAWING
    std::string output = d->draw();
    std::cout << output;

    // WRITE OUTPUT
    p.write_result(path_output, output);

    return 0;
}
