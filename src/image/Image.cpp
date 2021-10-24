#include "Image.hpp"

Image::Image(int height, int width) : height(height), width(width)
{
    this->black = new Pixel(0, 0, 0, 255);

    this->pxls.resize(height, std::vector<Pixel *>(width));
    
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            pxls[i][j] = this->black;
}

Image::~Image()
{
    delete this->black;
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

std::vector<Pixel *> &Image::operator[](int i)
{
    return this->pxls[i];
}
