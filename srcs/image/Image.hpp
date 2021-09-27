#pragma once

#include <vector>
#include "../pixel/Pixel.hpp"

class Image
{
private:
    int width;
    int height;
    std::vector< std::vector<Pixel> > pxls;

public:
    Image();
    Image(int width, int height);
    Image(int width, int height, std::vector< std::vector<Pixel> > pxls);
    ~Image();

    void load_pixels(std::vector< std::vector<Pixel> > pxls);
    void set_pixel(int x, int y, Pixel pxl);

    bool is_valid(int width, int height);

    Image &operator=(const Image &img);
    std::vector<Pixel> &operator[](int i);
};