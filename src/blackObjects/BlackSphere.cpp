#include "BlackSphere.hpp"

BlackSphere::BlackSphere(double x, double y, double z, double r) : BlackObject(), p(x, y, z)
{
    this->r = r;
}

BlackSphere::BlackSphere(Point &p, double r) : BlackObject(), p(p)
{
    this->r = r;
}
BlackSphere::~BlackSphere() {}

bool BlackSphere::contains(Point &p)
{
    return this->p.distWith(p) <= this->r;
}