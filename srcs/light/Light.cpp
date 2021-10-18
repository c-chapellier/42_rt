#include "Light.hpp"

Light::Light(double px, double py, double pz)
{
    this->p = new Point(px, py, pz);
}

Light::Light(Point *p) : p(p)
{

}

Light::~Light()
{
    delete this->p;
}
