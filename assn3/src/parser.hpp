#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

const char SEP = '|';

class parser {
private: 
    template <typename T>
    using cast = T (*)(const std::string&);

    /**
     * @brief split given string by given delimiter
     * @tparam T type of each separated value
     * @param s string to be split
     * @param delimiter delimiter
     * @param cast_ function to cast string to T
     * @return std::vector of T each of whose elements is separated by given delimiter
    */
    template <typename T>
    std::vector<T> split(const std::string &s, const char delimiter, const cast<T> cast_ = nullptr) const;
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

template <typename T>
std::vector<T> parser::split(const std::string &s, const char delimiter, const cast<T> cast_) const {
    std::vector<std::string> v_ = split<std::string>(s, delimiter, nullptr);
    std::vector<T> v;
    for (const std::string &s_ : v_) v.push_back(cast_(s_));
    return v;
}

template <>
std::vector<std::string> parser::split<std::string>(const std::string &s, const char delimiter, const cast<std::string> cast_) const {
    std::vector<std::string> v;
    
    std::istringstream iss(s);
    std::string buf_;
    while (getline(iss, buf_, delimiter))
        v.push_back(buf_);

    return v;
}

#endif