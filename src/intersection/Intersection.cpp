#include "Intersection.hpp"

Intersection::Intersection(double px, double py, double pz, double dist, Object *obj) : p(px, py, pz), dist(dist)
{
    this->obj = obj;
    this->tr = NULL;
}
Intersection::Intersection(const Point &p, double dist, Object *obj) : p(p), dist(dist)
{
    this->obj = obj;
    this->tr = NULL;
}
Intersection::Intersection(double px, double py, double pz, double dist, Object *obj, Triangle *tr) : p(px, py, pz), dist(dist)
{
    this->obj = obj;
    this->tr = tr;
}
Intersection::Intersection(const Point &p, double dist, Object *obj, Triangle *tr) : p(p), dist(dist)
{
    this->obj = obj;
    this->tr = tr;
}
Intersection::~Intersection() {}

Point Intersection::getP() const
{
    return this->p;
}
double Intersection::getDist() const
{
    return this->dist;
}
Object *Intersection::getObj() const
{
    return this->obj;
}
Triangle *Intersection::getTr() const
{
    return this->tr;
}

Intersection &Intersection::operator=(const Intersection &inter)
{
    this->p = inter.p;
    this->dist = inter.dist;
    this->obj = inter.obj;
    this->tr = inter.tr;
    return *this;
}

std::ostream& operator<< (std::ostream& out, const Intersection& inter)
{
    out << "Intersection{" << std::endl 
    << inter.getP() << std::endl
    << "Dist(" << inter.dist << ")" << std::endl
    << "}" << std::endl;
    return out;
}