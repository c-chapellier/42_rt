#include "Image.hpp"

Image::Image()
    : width(0), height(0)
{
    
}

Image::Image(int width, int height)
    : width(width), height(height)
{
    
}

Image::Image(int width, int height, std::vector< std::vector<Pixel> > pxls)
    : width(width), height(height), pxls(pxls)
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

bool Image::is_valid(int width, int height)
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
