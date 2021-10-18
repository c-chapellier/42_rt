#include "Pixel.hpp"

Pixel::Pixel()
{
    this->color = new Color(0, 0, 0, 255);
    this->dist = INFINITY;
}

Pixel::Pixel(int red, int green, int blue, int opacity, double dist)
{
    this->color = new Color(red, green, blue, opacity);
    this->dist = dist;
}

Pixel::Pixel(Color *c, double dist)
{
    this->color = new Color(*c);
    this->dist = dist;
}

Pixel::~Pixel()
{
    //delete(this->color);
}

int Pixel::get_red()
{
    return this->color->getR();
}

int Pixel::get_green()
{
    return this->color->getG();
}

int Pixel::get_blue()
{
    return this->color->getB();
}
Color *Pixel::getColor()
{
    return this->color;
}

int Pixel::get_opacity()
{
    return this->color->getO();
}

double Pixel::get_dist()
{
    return this->dist;
}

void Pixel::setColor(Color *color)
{
    this->color = color;
}
void Pixel::setDist(double dist)
{
    this->dist = dist;
}

Pixel &Pixel::operator=(const Pixel &pxl)
{
    //delete(this->color);
    this->color = new Color(*pxl.color);
    this->dist = pxl.dist;
    return *this;
}