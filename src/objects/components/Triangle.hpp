#pragma once

#include <vector>
#include "Point.hpp"
#include "Vector.hpp"
#include "./../Plane.hpp"

class Plane;

class Triangle
{
    private:
        Point p1;
        Point p2;
        Point p3;
    public:
        Triangle(const Point &p1, const Point &p2, const Point &p3);
        Triangle(Point *p1, Point *p2, Point *p3);
        ~Triangle();

        Plane getPlane() const;

        void intersect(std::vector<Intersection> *intersections, const Line &l, Object *obj) const;
};