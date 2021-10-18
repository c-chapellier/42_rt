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
    Image();
    Image(int height, int width);
    Image(int height, int width, std::vector< std::vector<Pixel> > pxls);
    ~Image();

    void load_pixels(std::vector< std::vector<Pixel> > pxls);
    void set_pixel(int x, int y, Pixel pxl);

    bool is_valid(int height, int width);

    Image &operator=(const Image &img);
    std::vector<Pixel> &operator[](int i);
};