#include "Plane.hpp"

Plane::Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz)
{
    Point *p = new Point(px, py, pz);
    Vector *v = new Vector(vx, vy, vz);
    this->p = p;
    this->v = v;
}

Plane::~Plane()
{
}

std::ostream& operator<< (std::ostream& out, const Plane& plane)
{
    out << "Plane : {" << std::endl
    << "\tpoint : " << *plane.p << std::endl
    << "\vector : " << *plane.v << std::endl
    << "}";
    return out;
}