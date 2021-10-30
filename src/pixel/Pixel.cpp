#include "Pixel.hpp"

Pixel::Pixel() : color(0, 0, 0, 255), dist(INFINITY), location_3d(), obj(NULL)
{
}

Pixel::Pixel(int red, int green, int blue, int opacity, double dist) : color(red, green, blue, opacity), dist(dist), location_3d(), obj(NULL)
{
}

Pixel::Pixel(Color *c, double dist): color(*c), dist(dist), location_3d(), obj(NULL)
{
}

Pixel::~Pixel()
{

}

int Pixel::getRed() const
{
    return this->color.getR();
}

int Pixel::getGreen() const
{
    return this->color.getG();
}

int Pixel::getBlue() const
{
    return this->color.getB();
}
Color &Pixel::getColor()
{
    return this->color;
}

int Pixel::getOpacity() const
{
    return this->color.getO();
}

double Pixel::get_dist() const
{
    return this->dist;
}

Point &Pixel::get_location()
{
    return this->location_3d;
}

Object *Pixel::get_object()
{
    return this->obj;
}

void Pixel::setColor(const Color &color)
{
    // std::cout << "setColor red[" << color.getR() << "]" << std::endl;
    this->color.setR(color.getR());
    this->color.setG(color.getG());
    this->color.setB(color.getB());
    this->color.setO(color.getO());
    // std::cout << "end setColor red[" << this->color.getR() << "]" << std::endl;
}

void Pixel::setLocation(const Point &p)
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
    // std::cout << "op= red[" << pxl.getRed() << "]" << std::endl;
    this->setColor(pxl.color);
    this->dist = pxl.dist;
    this->obj = pxl.obj;
    this->setLocation(pxl.location_3d);
    return *this;
}