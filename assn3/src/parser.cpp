#include "parser.hpp"

template <>
std::vector<std::string> parser::split<std::string>(const std::string &s, const char delimiter, const cast<std::string> cast_) const {
    std::vector<std::string> v; // vector to be returned, type of whose elements is std::string
    std::istringstream iss(s); // use std::istringstream to split std::string object
    std::string buf_; // declare a temporary buffer to store each separated string
    while (getline(iss, buf_, delimiter)) // repeatedly get string separated by delimiter
        v.push_back(buf_); // push it to v
    return v;
}

std::vector<int> parser::load_image(const char *input_file) const {
    std::ifstream in_file(input_file); // declare input file stream
    std::string _data; // declare a temporary buffer to store the whole line
    getline(in_file, _data); // read a line from input file (ignore lines below the first line)
    return split<int>(_data, SEP, [](const std::string &s) {return std::stoi(s);}); // pass an anonymous function to cast<std::string> to convert std::string to int
}

std::vector<std::string> parser::load_config(const char *input_file) const {
    std::ifstream in_file(input_file);
    std::string _data; // declare a temporary buffer to store the whole line
    getline(in_file, _data); // read a line from input config file (ignore lines below the first line)
    return split<std::string>(_data, SEP); // split it by SEP and return
}

void parser::write_result(const char *output_file, const std::string &result) const {
    std::ofstream out_file(output_file); // declare output file stream
    out_file << result; // write result to output file
    out_file.close(); // close output file stream
}
