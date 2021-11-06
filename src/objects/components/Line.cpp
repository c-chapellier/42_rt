#include "Line.hpp"

Line::Line(double px, double py, double pz, double vx, double vy, double vz)
    : p(px, py, pz), v(vx, vy, vz)
{
}

Line::Line(const Point &p, const Vector &v)
    : p(p), v(v)
{
}

Line::Line(const Point &a, const Point &b)
    : p(a), v(a, b)
{
}

Line::~Line()
{
}

Point &Line::getP()
{
    return this->p;
}

Point Line::getP() const
{
    return this->p;
}

Vector &Line::getV()
{
    return this->v;
}

Vector Line::getV() const
{
    return this->v;
}

double Line::distWith(const Point &p) const
{
    Vector tmp(this->p, p);
    double dist = tmp.crossProductMagnitude(this->v) / this->v.getMagnitude();
    return dist;
}

Point Line::getPointFor(double t) const
{
    Point tmp(this->p.getX() + (this->v.getX() * t), this->p.getY() + (this->v.getY() * t), this->p.getZ() + (this->v.getZ() * t));
    return tmp;
}

Point Line::getPointAt(double dist) const
{
    double t = dist / this->v.getMagnitude();
    return Point(this->p.getX() + (this->v.getX() * t), this->p.getY() + (this->v.getY() * t), this->p.getZ() + (this->v.getZ() * t));
}

std::ostream& operator<< (std::ostream& out, const Line& line)
{
    out << "Line : {" << std::endl
    << "\tpoint: " << line.p << std::endl
    << "\tvector: " << line.v << std::endl
    << '}' << std::endl;
    return out;
}