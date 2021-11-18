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
        Triangle(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z, double p3x, double p3y, double p3z);
        Triangle(const Point &p1, const Point &p2, const Point &p3);
        Triangle(Point *p1, Point *p2, Point *p3);
        Triangle(const Triangle &triangle);
        ~Triangle();

        Point &getP1();
        Point &getP2();
        Point &getP3();
        Plane getPlane() const;

        std::vector<Intersection> intersect(const Line &l) const;
};