#include "Pixel.hpp"

Pixel::Pixel()
{

}

Pixel::Pixel(int red, int green, int blue, int opacity)
    : red(red), green(green), blue(blue), opacity(opacity)
{

}

Pixel::Pixel(Color *c)
{
    this->red = c->getR();
    this->green = c->getG();
    this->blue = c->getB();
    this->opacity = c->getO();
}

Pixel::~Pixel()
{

}

int Pixel::get_red()
{
    return this->red;
}

int Pixel::get_green()
{
    return this->green;
}

int Pixel::get_blue()
{
    return this->blue;
}

int Pixel::get_opacity()
{
    return this->opacity;
}

Pixel &Pixel::operator=(const Pixel &pxl)
{
    this->red = pxl.red;
    this->blue = pxl.blue;
    this->green = pxl.green;
    this->opacity = pxl.opacity;
    return *this;
}