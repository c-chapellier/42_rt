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

}

int Pixel::getRed() const
{
    return this->color->getR();
}

int Pixel::getGreen() const
{
    return this->color->getG();
}

int Pixel::getBlue() const
{
    return this->color->getB();
}
Color *Pixel::getColor()
{
    return this->color;
}

int Pixel::getOpacity() const
{
    return this->color->getO();
}

double Pixel::get_dist() const
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

void Pixel::setColor(const Color &color)
{
    this->color->setR(color.getR());
    this->color->setG(color.getG());
    this->color->setB(color.getB());
    this->color->setO(color.getO());
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
    this->color = new Color(*pxl.color);
    this->dist = pxl.dist;
    return *this;
}