#include "parser.hpp"

std::vector<int> parser::load_image(const char *input_file) {
    std::ifstream in_file(input_file);
    if (!in_file.is_open())
        throw std::runtime_error("Unable to open file");

    std::string _data;
    getline(in_file, _data);
    return split<int>(_data, SEP, [](const std::string &s) {return std::stoi(s);});
}

std::vector<std::string> parser::load_config(const char *input_file) {
    std::ifstream in_file(input_file);
    if (!in_file.is_open())
        throw std::runtime_error("Unable to open file");

    std::string _data;
    getline(in_file, _data);
    return split<std::string>(_data, SEP);
}

void parser::write_result(const char *output_file, const std::string &result) {
    std::ofstream out_file(output_file);
    out_file << result;
    out_file.close();
}
