#include "Line.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Line::Line(double px, double py, double pz, double vx, double vy, double vz)
    : p(px, py, pz), v(vx, vy, vz)
{}

Line::Line(const Point &p, const Vector &v)
    : p(p), v(v)
{}

Line::Line(const Point &a, const Point &b)
    : p(a), v(a, b)
{}

Line::Line(const Point &a, double x, double y, double z)
    :p(a), v(a, x, y, z)
{}

Line::~Line(){}

/* * * * * * * * * * * * * * * * * * * * *

*                GETTER                  *

* * * * * * * * * * * * * * * * * * * * */

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

double Line::getX() const
{
    return this->v.getX();
}
double Line::getY() const
{
    return this->v.getY();
}
double Line::getZ() const
{
    return this->v.getZ();
}
double Line::getPX() const
{
    return this->p.getX();
}
double Line::getPY() const
{
    return this->p.getY();
}
double Line::getPZ() const
{
    return this->p.getZ();
}

/* * * * * * * * * * * * * * * * * * * * *

*              FUNCTIONS                 *

* * * * * * * * * * * * * * * * * * * * */

void Line::normalize()
{
    this->v.normalize();
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

/* * * * * * * * * * * * * * * * * * * * *

*              OPERATORS                 *

* * * * * * * * * * * * * * * * * * * * */

std::ostream& operator<< (std::ostream& out, const Line& line)
{
    out << "Line : {" << std::endl
    << "\tpoint: " << line.p << std::endl
    << "\tvector: " << line.v << std::endl
    << '}' << std::endl;
    return out;
}