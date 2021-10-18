#include "Pixel.hpp"

Pixel::Pixel() : 
    red(0),
    green(0),
    blue(0),
    opacity(255),
    dist(INFINITY)
{

}

Pixel::Pixel(int red, int green, int blue, int opacity, double dist) : 
    red(red),
    green(green),
    blue(blue),
    opacity(opacity),
    dist(dist)
{

}

Pixel::Pixel(Color *c, double dist) :
    dist(dist)
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

double Pixel::get_dist()
{
    return this->dist;
}

Pixel &Pixel::operator=(const Pixel &pxl)
{
    this->red = pxl.red;
    this->blue = pxl.blue;
    this->green = pxl.green;
    this->opacity = pxl.opacity;
    this->dist = pxl.dist;
    return *this;
}