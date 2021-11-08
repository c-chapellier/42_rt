#include "Image.hpp"

Image::Image(int height, int width) : height(height), width(width)
{
    this->pxls.resize(height, std::vector<Pixel>(width));
}

Image::Image(Image *img)
{
    this->height = img->height;
    this->width = img->width;
    this->pxls = img->pxls;
}

Image::~Image()
{
}

std::vector< std::vector<Pixel> > Image::getPixels()
{
    return this->pxls;
}

bool Image::is_valid(int height, int width) const
{
    return this->height == height && this->width == width;
}

Image &Image::operator=(const Image &img)
{
    this->height = img.height;
    this->width = img.width;
    this->pxls = img.pxls;
    return *this;
}

std::vector<Pixel> &Image::operator[](int i)
{
    return this->pxls[i];
}
