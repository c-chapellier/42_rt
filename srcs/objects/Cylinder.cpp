#include "Cylinder.hpp"

Cylinder::Cylinder(double px, double py, double pz, double vx, double vy, double vz, double r)
{
    this->p = new Point(px, py, pz);
    this->v = new Vector(vx, vy, vz);
    this->r = r;
}

Cylinder::~Cylinder()
{
    delete(this->p);
    delete(this->v);
}

std::ostream& operator<< (std::ostream& out, const Cylinder& cylinder)
{
    out << "Cylinder : {" << std::endl
    << "\tradius: " << cylinder.r << std::endl
    << "\tcenter: " << *cylinder.p << std::endl
    << "\tvector: " << *cylinder.v << std::endl
    << '}' << std::endl;
    return out;
}
