#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <fstream>
#include <string>
#include <vector>

class parser {
public: 
    /**
     * @brief Load image from file
     * @param input_file path to input image file (whose contents width, height, pixels are separated by |)
     * @return std::vector of integers representing image
    */
    std::vector<int> load_image(const char *input_file);
    
    /**
     * @brief Load configuration from file
     * @param input_file path to config file (whose contents are separated by |)
     * @return std::vector of strings representing config (artist class, drawer class)
    */
    std::vector<std::string> load_config(const char *input_file);

    /**
     * @brief write result to file (as string)
     * @param output_file path to output file
     * @return none
    */
    void write_result(const char *output_file, const std::string &result);
};

#endif