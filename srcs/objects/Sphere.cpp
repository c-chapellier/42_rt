#include "Sphere.hpp"

Sphere::Sphere(double x, double y, double z, double r) : r(r)
{
    Point *p = new Point(x, y, z);
    this->center = p;
}

Sphere::~Sphere()
{
    delete(this->center);
}

std::ostream& operator<< (std::ostream& out, const Sphere& sp)
{
    out << "Sphere : {" << std::endl
    << "\tradius: " << sp.r << std::endl
    << "\tcenter: " << *sp.center << std::endl 
    << '}' << std::endl;
    return out;
}