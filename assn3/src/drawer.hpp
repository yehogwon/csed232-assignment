#ifndef __DRAWER_HPP__
#define __DRAWER_HPP__

#include <string>
#include "artist.hpp"

class drawer {
public: 
    void drawer(artist*);
    virtual std::string draw();
};

class downsample : public drawer {
public: 
    std::string draw();
};

class upsample : public drawer {
public: 
    std::string draw();
};

class scale : public drawer {
public: 
    scale(artist*, int, int);
    std::string draw();
};

#endif