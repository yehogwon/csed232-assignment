#ifndef __DRAWER_HPP__
#define __DRAWER_HPP__

#include <string>
#include <sstream>
#include "artist.hpp"

class drawer {
protected: 
    artist *artist_;
public: 
    /**
     * @brief A constructor for the drawer class
     * @param artist_ A pointer to an artist object
    */
    drawer(artist *artist_);

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
    int x_ratio, y_ratio;
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