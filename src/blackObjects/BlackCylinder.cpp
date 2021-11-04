#include "BlackCylinder.hpp"

BlackCylinder::BlackCylinder(double px, double py, double pz, double vx, double vy, double vz, double r) : BlackObject(), l(px, py, pz, vx, vy, vz)
{
    this->r = r;
}

BlackCylinder::BlackCylinder(Point &p, Vector &v, double r) : BlackObject(), l(p, v)
{
    this->r = r;
}

BlackCylinder::BlackCylinder(Line &line, double r) : BlackObject(), l(line)
{
    this->r = r;
}
BlackCylinder::~BlackCylinder() {}

bool BlackCylinder::contains(Point &p)
{
    double dist = this->l.distWith(p);
    return dist <= this->r;
}