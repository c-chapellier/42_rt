#include "Light.hpp"

Light::Light(double px, double py, double pz, Color *color) : color(color)
{
    this->p = new Point(px, py, pz);
}

Light::~Light()
{
    delete this->p;
}

Point *Light::getP()
{
    return this->p;
}

Color *Light::getColor()
{
    return this->color;
}
