#include "Image.hpp"

Image::Image() : height(0), width(0)
{
    
}

Image::Image(int height, int width) : height(height), width(width)
{
    pxls.resize(height, std::vector<Pixel>(width));
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            pxls[i][j] = Pixel(0, 0, 0, 255);
}

Image::Image(int height, int width, std::vector< std::vector<Pixel> > pxls) : height(height), width(width), pxls(pxls)
{
    
}

Image::~Image()
{
    
}


void Image::load_pixels(std::vector< std::vector<Pixel> > pxls)
{
    this->pxls = pxls;
}

void Image::set_pixel(int x, int y, Pixel pxl)
{
    this->pxls[x][y] = pxl;
}

bool Image::is_valid(int height, int width)
{
    return this->width == width && this->height == height;
}

Image &Image::operator=(const Image &img)
{
    this->width = img.width;
    this->height = img.height;
    this->pxls = img.pxls;
    return *this;
}

std::vector<Pixel> &Image::operator[](int i)
{
    return this->pxls[i];
}
