#include "Image.hpp"

Image::Image(int height, int width) : height(height), width(width)
{
    this->pxls.resize(height, std::vector<Pixel>(width));
}

Image::Image(Image *img)
{
    this->width = img->width;
    this->height = img->height;
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
