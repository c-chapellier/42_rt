#include "Light.hpp"

Light::Light(double px, double py, double pz, const Color &color)
    : p(px, py, pz), color(color)
{
}

Light::~Light()
{
}

Point Light::getP() const
{
    return this->p;
}

Color Light::getColor() const
{
    return this->color;
}
