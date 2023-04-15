#ifndef __ARTIST_HPP__
#define __ARTIST_HPP__

#include <vector>

class artist {
public: 
    artist(int, int, const std::vector<int>&);
    virtual char mapper(int, int);
};

class classic : public artist {
public:
    char mapper(int, int);
};

class iclassic : public artist {
public:
    char mapper(int, int);
};

class sobelx : public artist {
public:
    char mapper(int, int);
};

class sobely : public artist {
public:
    char mapper(int, int);
};

class gradient : public artist {
public:
    char mapper(int, int);
};

#endif