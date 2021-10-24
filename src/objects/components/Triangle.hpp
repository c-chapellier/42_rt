#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "./../Plane.hpp"

class Plane;

class Triangle
{
    private:
        Point *p1;
        Point *p2;
        Point *p3;
    public:
        Triangle(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z, double p3x, double p3y, double p3z);
        Triangle(Point *p1, Point *p2, Point *p3);
        Triangle(Point &p1, Point &p2, Point &p3);
        Triangle(Triangle &triangle);
        ~Triangle();

        Point *getP1();
        Point *getP2();
        Point *getP3();
        Plane *getPlane();

        Point *intersect(Line *l);
};