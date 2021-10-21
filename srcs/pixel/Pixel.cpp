#include "Pixel.hpp"

Pixel::Pixel()
{
    this->color = new Color(0, 0, 0, 255);
    this->dist = INFINITY;
    this->obj = NULL;
}

Pixel::Pixel(int red, int green, int blue, int opacity, double dist)
{
    this->color = new Color(red, green, blue, opacity);
    this->dist = dist;
    this->obj = NULL;
}

Pixel::Pixel(Color *c, double dist)
{
    this->color = new Color(*c);
    this->dist = dist;
    this->obj = NULL;
}

Pixel::~Pixel()
{
    //delete(this->color);
}

int Pixel::getRed()
{
    return this->color->getR();
}

int Pixel::getGreen()
{
    return this->color->getG();
}

int Pixel::getBlue()
{
    return this->color->getB();
}
Color *Pixel::getColor()
{
    return this->color;
}

int Pixel::getOpacity()
{
    return this->color->getO();
}

double Pixel::get_dist()
{
    return this->dist;
}

Point *Pixel::get_location()
{
    return this->location_3d;
}

Object *Pixel::get_object()
{
    return this->obj;
}

void Pixel::setColor(Color *color)
{
    this->color = color;
}

void Pixel::setLocation(Point *p)
{
    this->location_3d = p;
}

void Pixel::setDist(double dist)
{
    this->dist = dist;
}

void Pixel::setObject(Object *obj)
{
    this->obj = obj;
}

Pixel &Pixel::operator=(const Pixel &pxl)
{
    //delete(this->color);
    this->color = new Color(*pxl.color);
    this->dist = pxl.dist;
    return *this;
}