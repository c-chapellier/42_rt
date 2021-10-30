#include "BlackSphere.hpp"

BlackSphere::BlackSphere(double x, double y, double z, double r) : BlackObject()
{
    this->p = new Point(x, y, z);
    this->r = r;
}

BlackSphere::BlackSphere(Point *p, double r) : BlackObject()
{
    this->p = new Point(*p);
    this->r = r;
}
BlackSphere::~BlackSphere()
{
    delete(this->p);
}

bool BlackSphere::contains(Point *p)
{
    return this->p->distWith(*p) <= this->r;
}