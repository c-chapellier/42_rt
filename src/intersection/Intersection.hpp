#pragma once

#include "./../objects/components/Point.hpp"
class Object;
class Triangle;

class Intersection
{
    private:
        Point p;
        double dist;
        Object *obj;
        Triangle *tr;
    public:
        Intersection(double px, double py, double pz, double dist, Object *obj);
        Intersection(const Point &p, double dist, Object *obj);
        Intersection(double px, double py, double pz, double dist, Object *obj, Triangle *tr);
        Intersection(const Point &p, double dist, Object *obj, Triangle *tr);
        ~Intersection();

        Point getP() const;
        double getDist() const;
        Object *getObj() const;
        Triangle *getTr() const;

        Intersection &operator=(const Intersection &inter);
};