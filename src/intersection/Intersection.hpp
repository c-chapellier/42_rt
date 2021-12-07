#pragma once

#include "./../objects/components/Point.hpp"
class Object;
class Triangle;

class Intersection
{
    private:
        Point real_point;
        Point local_point;
        double dist;
        Object *obj;
        Triangle *tr;
    public:
        Intersection(const Point &real, const Point &local, double dist, Object *obj);
        Intersection(const Point &real, const Point &local, double dist, Object *obj, Triangle *tr);
        ~Intersection();

        Point getRealPoint() const;
        Point getLocalPoint() const;
        double getDist() const;
        Object *getObj() const;
        Triangle *getTr() const;

        Intersection &operator=(const Intersection &inter);

        friend std::ostream& operator<<(std::ostream& out, const Intersection& point);
};