#pragma once

#include <vector>
#include "../pixel/Pixel.hpp"

class Pixel;

class Image
{
private:
    int height;
    int width;
    std::vector< std::vector<Pixel> > pxls;

public:
    Image(int height, int width);
    Image(Image *img);
    ~Image();

    bool is_valid(int height, int width);

    Image &operator=(const Image &img);
    std::vector<Pixel> &operator[](int i);
};