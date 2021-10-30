#include "BlackCylinder.hpp"

BlackCylinder::BlackCylinder(double px, double py, double pz, double vx, double vy, double vz, double r) : BlackObject()
{
    this->l = new Line(px, py, pz, vx, vy, vz);
    this->r = r;
}

BlackCylinder::BlackCylinder(Point *p, Vector *v, double r) : BlackObject()
{
    this->l = new Line(*p, *v);
    this->r = r;
}

BlackCylinder::BlackCylinder(Line *line, double r) : BlackObject()
{
    this->l = new Line(*line);
    this->r = r;
}
BlackCylinder::~BlackCylinder()
{
    delete(this->l);
}

bool BlackCylinder::contains(Point *p)
{
    double dist = this->l->distWith(*p);
    return dist <= this->r;
}