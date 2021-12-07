#include "Intersection.hpp"

Intersection::Intersection(const Point &real, const Point &local, double dist, Object *obj)
    : real_point(real), local_point(local), dist(dist)
{
    this->obj = obj;
    this->tr = NULL;
}

Intersection::Intersection(const Point &real, const Point &local, double dist, Object *obj, Triangle *tr)
    : real_point(real), local_point(local), dist(dist)
{
    this->obj = obj;
    this->tr = tr;
}

Intersection::~Intersection() {}

Point Intersection::getRealPoint() const
{
    return this->real_point;
}
Point Intersection::getLocalPoint() const
{
    return this->local_point;
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
    this->real_point = inter.real_point;
    this->local_point = inter.local_point;
    this->dist = inter.dist;
    this->obj = inter.obj;
    this->tr = inter.tr;
    return *this;
}

std::ostream& operator<< (std::ostream& out, const Intersection& inter)
{
    out << "Intersection{" << std::endl 
    << inter.getRealPoint() << std::endl
    << "Dist(" << inter.dist << ")" << std::endl
    << "}" << std::endl;
    return out;
}