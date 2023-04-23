#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

const char SEP = '|'; // delimiter of input file

class parser {
private: 
    template <typename T>
    using cast = T (*)(const std::string&); // declare cast function pointer type (const std::string& -> T)

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
    std::vector<int> load_image(const char *input_file) const;
    
    /**
     * @brief Load configuration from file
     * @param input_file path to config file (whose contents are separated by |)
     * @return std::vector of strings representing config (artist class, drawer class)
    */
    std::vector<std::string> load_config(const char *input_file) const;

    /**
     * @brief write result to file (as string)
     * @param output_file path to output file
     * @return none
    */
    void write_result(const char *output_file, const std::string &result) const;
};

template <typename T>
inline std::vector<T> parser::split(const std::string &s, const char delimiter, const cast<T> cast_) const {
    std::vector<std::string> v_ = split<std::string>(s, delimiter, nullptr); // split string by delimiter in std::string type
    std::vector<T> v; // vector to be returned, type of whose elements is T
    for (const std::string &s_ : v_) v.push_back(cast_(s_)); // cast each element of v_ to T and push it to v using cast_
    return v;
}

// explicit specialization of parser::split for std::string
template <>
std::vector<std::string> parser::split<std::string>(const std::string &s, const char delimiter, const cast<std::string> cast_) const;

#endif