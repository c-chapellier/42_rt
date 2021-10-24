#include "Line.hpp"

Line::Line(double px, double py, double pz, double vx, double vy, double vz)
{
    this->p = new Point(px, py, pz);
    this->v = new Vector(vx, vy, vz);
}

Line::Line(Point *p, Vector *v)
{
    this->p = p;
    this->v = v;
}

Line::Line(Point *a, Point *b)
{
    this->p = new Point(*a);
    this->v = new Vector(*a, *b);
}

Line::~Line()
{
    delete(this->p);
    delete(this->v);
}

Point *Line::getP()
{
    return this->p;
}
Vector *Line::getV()
{
    return this->v;
}

double Line::distWith(Point &p)
{
    Vector tmp(*this->p, p);
    double dist = tmp.crossProductMagnitude(this->v) / this->v->getMagnitude();
    return dist;
}

Point *Line::getPointFor(double t)
{
    return new Point(this->p->getX() + (this->v->getX() * t), this->p->getY() + (this->v->getY() * t), this->p->getZ() + (this->v->getZ() * t));
}

Point *Line::getPointAt(double dist)
{
    double l = this->v->getMagnitude();
    double t = dist / l;
    return new Point(this->p->getX() + (this->v->getX() * t), this->p->getY() + (this->v->getY() * t), this->p->getZ() + (this->v->getZ() * t));
}

std::ostream& operator<< (std::ostream& out, const Line& line)
{
    out << "Line : {" << std::endl
    << "\tpoint: " << *line.p << std::endl
    << "\tvector: " << *line.v << std::endl
    << '}' << std::endl;
    return out;
}