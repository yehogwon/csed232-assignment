#ifndef __DRAWER_HPP__
#define __DRAWER_HPP__

#include <string>
#include <sstream>
#include "artist.hpp"

class drawer {
protected: 
    artist *artist_; // pointer to an artist object

    /**
     * @brief A helper function for the draw() function (gets stretching factors and steps). For both directions, at least one of the factor and step must be 1. 
     * @param i_factor The factor to stretch the i-axis (vertical) by
     * @param i_step The step to take on the i-axis
     * @param j_factor The factor to stretch the j-axis (horizontal) by
     * @param j_step The step to take on the j-axis
     * @return ASCII art as a std::string
    */
    inline std::string draw_helper(int i_factor, int i_step, int j_factor, int j_step) const;
public: 
    /**
     * @brief A constructor for the drawer class
     * @param artist_ A pointer to an artist object
    */
    drawer(artist *artist_);

    /**
     * @brief A destructor for the drawer class (virtual). Deletes the artist object. 
    */
    virtual ~drawer();

    /**
     * @brief Draw ASCII art
     * @return ASCII art as a std::string
    */
    virtual std::string draw() const;
};

class downsample : public drawer {
public: 
    /**
     * @brief A constructor for the downsample class
     * @param artist_ A pointer to an artist object
    */
    downsample(artist *artist_);

    /**
     * @brief Draw ASCII art and downsample by a factor of 2
     * @return ASCII art as a std::string
    */
    std::string draw() const;
};

class upsample : public drawer {
public: 
    /**
     * @brief A constructor for the upsample class
     * @param artist_ A pointer to an artist object
    */
    upsample(artist *artist_);

    /**
     * @brief Draw ASCII art and upsample by a factor of 2
     * @return ASCII art as a std::string
    */
    std::string draw() const;
};

class scale : public drawer {
private: 
    int i_length_factor, i_step, j_length_factor, j_step; // factors and steps for the i and j axes (more details are explained in scale::scale())
public: 
    /**
     * @brief A constructor for the scale class
     * @param artist_ A pointer to an artist object
     * @param x_ratio The ratio to scale the x-axis by
     * @param y_ratio The ratio to scale the y-axis by
    */
    scale(artist *artist_, int x_ratio, int y_ratio);

    /**
     * @brief Draw ASCII art and scale to the given ratio
     * @return ASCII art as a std::string
    */
    std::string draw() const;
};

#endif